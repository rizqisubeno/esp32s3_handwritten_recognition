#include <iostream>

// for use std::max_element
#include <c++/12.2.0/bits/stl_algo.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "lvgl/lvgl.h"

#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_xpt2046.h"

#include "lcd_touch_init.h"

//include gui from squareline studio
#include "squareline_ui/ui.h"

#include "lvgl_component_init.h"

#include "NeuralNetwork.h"

using namespace std;

static const char *TAG = "main";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LCD_PIXEL_CLOCK_HZ     (40 * 1000 * 1000)

#define PIN_NUM_LCD_SCLK       12
#define PIN_NUM_LCD_MOSI       11
#define PIN_NUM_LCD_MISO       13
#define PIN_NUM_LCD_DC         5
#define PIN_NUM_LCD_RST        4
#define PIN_NUM_LCD_CS         10
#define PIN_NUM_TOUCH_MISO     37 //tdout miso
#define PIN_NUM_TOUCH_MOSI     35 //tdin mosi
#define PIN_NUM_TOUCH_SCLK     36
#define PIN_NUM_TOUCH_CS       39
#define PIN_NUM_TOUCH_IRQ      40

#define LCD_H_RES              240
#define LCD_V_RES              320

#define LVGL_TASK_MAX_DELAY_MS 500
#define LVGL_TASK_MIN_DELAY_MS 1
#define LVGL_TASK_PRIORITY     3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// END CONFIGURATION ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BLINK_GPIO GPIO_NUM_48

TaskHandle_t taskInit = NULL;
TaskHandle_t taskLVGL = NULL;
TaskHandle_t taskPredict = NULL;

SemaphoreHandle_t lvgl_semaphore = NULL;

esp_lcd_touch_handle_t tp = NULL;

lv_disp_t *display_screen;
lv_indev_drv_t touch_input;

lvgl_struct_t my_lvgl_config;
lcd_touch_config_t my_config;

lv_obj_t *ui_changeScreen;

//for buffer image 
static uint8_t origImage[myCANVAS_WIDTH][myCANVAS_HEIGHT], downImage[DOWNSIZED_HEIGHT][DOWNSIZED_WIDTH];
static float downImageF[DOWNSIZED_WIDTH*DOWNSIZED_HEIGHT];


bool lvgl_lock(int timeout_ms)
{
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_semaphore, timeout_ticks) == pdTRUE;
   
}

//event when changing
void ui_changeScreenEvnt( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if ( event_code == LV_EVENT_SCREEN_LOAD_START) {
      titleSlide_Animation(ui_Title, 0);
      panelSlide_Animation(ui_MainPanel, 200);
    }
}

static void lvgl_background_task(void *arg)
{
    char percentage[8], timeNNLabel[10];
    float classNN[10], time_elapsed;
    uint8_t output_class_id;

    handleStruct myHandle = *(handleStruct*)arg;

    //waiting initialization finished then next instruction run
    while(!lvgl_lock(-1));

    //deleting the lcd_and_touch_init task
    vTaskDelete(taskInit);

    // giving semaphore
    xSemaphoreGiveRecursive(lvgl_semaphore);

    ESP_LOGI(TAG, "Starting LVGL main task");
    uint32_t task_delay_ms = 500;

    // lvgl calling ui edited with squareline studio
    ui_init();

    // looping until 8 seconds
    while ((int64_t)(esp_timer_get_time()/1000000.0f)<=8) {
        if (lvgl_lock(-1)) {
            task_delay_ms = lv_timer_handler();
            // Release the mutex (lvgl_unlock)
            xSemaphoreGiveRecursive(lvgl_semaphore);
            // xSemaphoreGive(lvgl_semaphore);
        }
        if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
        } else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
        }
        // printf("time count : %ld \r\n", time_counting);
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
    
    ESP_LOGI(TAG, "go to screen main");
    ui_changeScreen = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui_changeScreen, ui_changeScreenEvnt, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui_changeScreen);
    lv_disp_load_scr(ui_ScreenMain);

    //lvgl ui_screen_change
    _ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 8000, &ui_ScreenMain_screen_init);
    
    lv_obj_t *canvas;
    canvas = lv_canvas_create(ui_MainPanel);
    written_canvas myCanvas;
    myCanvas.canvas = canvas;
    myCanvas.isInvertColor = false;
    myCanvas.isEnabled = true;
    lvgl_component_init(&myHandle, &myCanvas);
    _ui_screen_delete(&ui_TitleScreen);

    while(1) {
        if (lvgl_lock(-1)) {
            task_delay_ms = lv_timer_handler();
            // Release the mutex (lvgl_unlock)
            xSemaphoreGiveRecursive(lvgl_semaphore);
            // xSemaphoreGive(lvgl_semaphore);

            if(myCanvas.isEnabled)
                lvgl_show_sign(my_lvgl_config.indev_drv);

            nnReceived dataStruct=receive_nn_data();
            if(dataStruct.status == pdPASS) 
            {
                memcpy(classNN, dataStruct.dataReceived, sizeof(float) * 10);
                output_class_id = (uint8_t)dataStruct.dataReceived[10];
                time_elapsed = dataStruct.dataReceived[11];
                lv_roller_set_selected(ui_Roller2, output_class_id, LV_ANIM_ON);

                lv_arc_set_value(ui_Arc2, (uint8_t)(classNN[output_class_id]*100));
                sprintf(percentage, "%.1f%%",(classNN[output_class_id]*100.0f));
                lv_label_set_text(ui_percentPredict, percentage);

                sprintf(timeNNLabel, "%.3f ms", time_elapsed);
                lv_label_set_text(ui_timeNN, timeNNLabel);

                lv_arc_set_value(ui_Arc2, (uint8_t)(classNN[output_class_id]*100));
                sprintf(percentage, "%.1f%%",(classNN[output_class_id]*100.0f));
                lv_label_set_text(ui_percentPredict, percentage);
            }
        }
    }
    
}

//neural predict task
static void nn_predict(void *arg)
{
    const char *TAG = "nn_predict";
    handleStruct myHandle = *(handleStruct*)arg;

    written_canvas nn_canvas;
    nn_canvas.isEnabled = true;
    lv_img_dsc_t *my_written_img;

    char buff_model_use[10];
    int model_number = 0;
    uint8_t buf1,buf2,output_class;
    int64_t time_first, time_elapsed;
    float *output_nn, outputData[12];

    //initialization neural network (for mnist only)
    nn_init1();
    nn_init2();

    while(1)
    {
        if(xQueueReceive(myHandle.nn_model_list, &buff_model_use, (TickType_t)portMAX_DELAY))
        {
            if(strcmp(buff_model_use,"cnn+mlp") == 0)
                {
                    ESP_LOGI(TAG,"cnn+mlp model selected");
                    model_number = 1;
                }
            else if(strcmp(buff_model_use,"mlp only") == 0)
                {
                    ESP_LOGI(TAG,"mlp only model selected");
                    model_number = 2;
                    }
        }
        if(xQueueReceive(myHandle.canvasHandle, &nn_canvas, (TickType_t)portMAX_DELAY))
        {
            ESP_LOGI(TAG, "queue received!");
            //wait 500 ms to predictpanel shows up on center
            vTaskDelay(pdMS_TO_TICKS(500));
            ESP_LOGI(TAG,"nn_predict ...");
            my_written_img = lv_canvas_get_img(nn_canvas.canvas);
            ESP_LOGI(TAG, "nn_canvas invert : %d", nn_canvas.isInvertColor);
            ESP_LOGI(TAG, "nn_canvas enabled : %d", nn_canvas.isEnabled);
            for (int y=0;y<myCANVAS_HEIGHT;y++)
            {
                for(int x=0;x<myCANVAS_WIDTH;x++)
                {      
                    // two times because format is 16-bit rgb :
                    // 3 bit lower (green) + 5 bit (blue),  5 bit lower (red) + 3 bit higher (green)
                    buf1 = my_written_img->data[(y*myCANVAS_WIDTH*2)+((x*2)+0)]; //first byte
                    buf2 = my_written_img->data[(y*myCANVAS_WIDTH*2)+((x*2)+1)]; //second byte
                    origImage[y][x] = (uint8_t)((buf1+buf2)/2);
                }
            }
            downsampleImage(origImage, downImage);
            for (int y=0;y<DOWNSIZED_HEIGHT;y++)
            {
                for(int x=0;x<DOWNSIZED_WIDTH;x++)
                {      
                    // downImageByte[y*DOWNSIZED_WIDTH+x] = downImage[y][x];
                    if (nn_canvas.isInvertColor)
                        downImageF[y*DOWNSIZED_WIDTH+x] = downImage[y][x]>=127 ? 0.0f : 1.0f;
                    else
                        downImageF[y*DOWNSIZED_WIDTH+x] = downImage[y][x]>=127 ? 1.0f : 0.0f;
                }
            }
            for(int x=0;x<DOWNSIZED_HEIGHT*DOWNSIZED_WIDTH;x++)
            {
                if (model_number==1)
                {getInputBuffer1()[x]=(float)(downImageF[x]);}
                else if (model_number==2)
                {getInputBuffer2()[x]=(float)(downImageF[x]);}
                
            }

            time_first = esp_timer_get_time();
            if (model_number==1)
                {output_nn=predict1();}
            else
                {output_nn=predict2();}
            time_elapsed = esp_timer_get_time()-time_first;
            output_class = std::distance(output_nn, std::max_element(output_nn, output_nn+10));
            ESP_LOGI(TAG,"output class : %d with percentage : %.2f", output_class, output_nn[output_class]*100.0f);
            
            memcpy(outputData, output_nn, sizeof(float) * 10);
            outputData[10] = (float)output_class;
            outputData[11] = (time_elapsed/1000.0f);
            xQueueSend(myHandle.dataHandle, outputData, (TickType_t)0);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

extern "C" void app_main(void)
{
    handleStruct myHandle;
    myHandle.canvasHandle = xQueueCreate(2, sizeof(written_canvas)); 
    // we create 11 array of float for 10 is class prob of nn 0-9 + class_id + with time elapsed on array 11.
    myHandle.dataHandle = xQueueCreate(2, sizeof(float [12]));
    // for queue communication list of nn model to use 
    myHandle.nn_model_list = xQueueCreate(2, sizeof(char [10])); 
    
    //check all handle must be not null 
    assert(myHandle.canvasHandle);
    assert(myHandle.dataHandle);
    assert(myHandle.nn_model_list);

    lvgl_semaphore = xSemaphoreCreateRecursiveMutex();
    assert(lvgl_semaphore);

    //lvgl handle display and touch 
    my_lvgl_config.disp=display_screen;
    my_lvgl_config.indev_drv=touch_input;
    
    //setup configuration for lcd and touch
    my_config.lcd_ver_res=320;
    my_config.lcd_hor_res=240;
    my_config.LCD_ROTATED=1;
    my_config.USE_TOUCH=1;
    my_config.lcd_spi_clock=LCD_PIXEL_CLOCK_HZ;
    my_config.lcd_sclk_pin=PIN_NUM_LCD_SCLK;
    my_config.lcd_mosi_pin=PIN_NUM_LCD_MOSI;
    my_config.lcd_dc_pin=PIN_NUM_LCD_DC;
    my_config.lcd_rst_pin=PIN_NUM_LCD_RST;
    my_config.lcd_cs_pin=PIN_NUM_LCD_CS;
    my_config.lcd_backlight_pin=-1;
    my_config.use_backlight=false;
    my_config.touch_sclk_pin=PIN_NUM_TOUCH_SCLK;
    my_config.touch_mosi_pin=PIN_NUM_TOUCH_MOSI;
    my_config.touch_miso_pin=PIN_NUM_TOUCH_MISO;
    my_config.touch_cs_pin=PIN_NUM_TOUCH_CS;
    my_config.touch_irq_pin=PIN_NUM_TOUCH_IRQ;
    my_config.use_touch_irq=true;
    my_config.touch_handle=tp;
    my_config.lvgl_handle=&my_lvgl_config;
    my_config.semaphore_handle=lvgl_semaphore;
    my_config.task=taskInit;

    //for initialization only, after that this task is suspended and deleted by lvgl_background
    xTaskCreatePinnedToCore(&lcd_and_touch_init, "ILI9341_XPT2046", 4*1024, &my_config, 4, &taskInit, 0);
    
    //for main lvgl program
    xTaskCreatePinnedToCore(&lvgl_background_task, "background_task", 8*1024, &myHandle, LVGL_TASK_PRIORITY, &taskLVGL, 0);

    // nn handwritten digit prediction
    xTaskCreatePinnedToCore(&nn_predict, "NN_predict", 12*1024, &myHandle, 3, &taskPredict, 1);
}