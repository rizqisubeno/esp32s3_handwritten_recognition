#include "lvgl_component_init.h"

static const char *TAG = "LVGL_COMPONENT_INIT";

lv_draw_rect_dsc_t myPoint;
lv_obj_t *ui_Roller1;

static uint16_t touch_x[1] = {0};
static uint16_t touch_y[1] = {0};

static written_canvas *local_canvas;

static uint8_t line_point = 14;
static float output_nn[10];

static QueueHandle_t canvasQueue, NNQueue, modelQueue;

double scaled(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
  return (double)((x - in_min) * (out_max - out_min)) / (double)((in_max - in_min)) + (double)out_min;
}

// Function to downsample an image
void downsampleImage(uint8_t originalImage[myCANVAS_HEIGHT][myCANVAS_WIDTH], uint8_t downsampledImage[DOWNSIZED_HEIGHT][DOWNSIZED_WIDTH]) {
    for (int y = 0; y < DOWNSIZED_HEIGHT; y++) {
        for (int x = 0; x < DOWNSIZED_WIDTH; x++) {
            int sum = 0;
            for (int dy = 0; dy < myCANVAS_HEIGHT / DOWNSIZED_HEIGHT; dy++) {
                for (int dx = 0; dx < myCANVAS_WIDTH / DOWNSIZED_WIDTH; dx++) {
                    int originalX = x * (myCANVAS_WIDTH / DOWNSIZED_WIDTH) + dx;
                    int originalY = y * (myCANVAS_HEIGHT / DOWNSIZED_HEIGHT) + dy;
                    sum += originalImage[originalY][originalX];
                }
            }
            downsampledImage[y][x] = (uint8_t)(sum / (myCANVAS_WIDTH / DOWNSIZED_WIDTH) / (myCANVAS_HEIGHT / DOWNSIZED_HEIGHT));
        }
    }
}

nnReceived receive_nn_data(void)
{
    float nnData[12];
    BaseType_t xStatus;
    nnReceived nnMessage;
    xStatus = xQueueReceive(NNQueue, &nnData, (TickType_t)0);
    if(xStatus == pdPASS)
    {
        memcpy(output_nn, nnData, sizeof(float) * 10);
        memcpy(nnMessage.dataReceived, nnData, sizeof(float) * 12);
    }

    nnMessage.status = xStatus;
    return nnMessage;
}

void delete_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        ESP_LOGI(TAG, "delete button clicked");
        if(local_canvas->isInvertColor)
            lv_canvas_fill_bg(local_canvas->canvas, lv_color_hex(0xffffff), LV_OPA_COVER);
        else
            lv_canvas_fill_bg(local_canvas->canvas, lv_color_hex(0x000000), LV_OPA_COVER);
    }
}

void predict_event_cb(lv_event_t * e)
{
    char data[10];
    lv_event_code_t code = lv_event_get_code(e);
    BaseType_t xStatus;
    if(code == LV_EVENT_CLICKED) {
        ESP_LOGI(TAG, "predict button clicked");
        predictSlide_Animation(ui_predictPanel, 0);
        local_canvas->isEnabled = false;
        ESP_LOGI(TAG, "local canvas invert : %d", local_canvas->isInvertColor);
        lv_roller_get_selected_str(ui_Roller1, data, 10);
        xStatus = xQueueSend(modelQueue, &data, (TickType_t)10);
        if(xStatus != pdPASS)
        {
            ESP_LOGE(TAG, "model queue cannot send");
        }
        else
        {
            ESP_LOGI(TAG, "model queue send done");
        }
        xStatus = xQueueSend(canvasQueue, local_canvas, (TickType_t)10);
        if(xStatus != pdPASS)
        {
            ESP_LOGE(TAG, "queue cannot send");
        }
        else
        {
            ESP_LOGI(TAG, "queue send done");
        }
    }
}

void applyBtn_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
    {
        // lv_switch_get_state(ui_colorSw)
        line_point = atoi(lv_label_get_text(ui_lineLabel));
        ESP_LOGI(TAG,"line point size : %d\r\n", line_point);
        if(lv_obj_has_state(ui_colorSw, LV_STATE_CHECKED))
        {
            lv_canvas_fill_bg(local_canvas->canvas, lv_color_hex(0xffffff), LV_OPA_COVER);
            myPoint.bg_color = lv_color_hex(0x000000);
            local_canvas->isInvertColor = true;
        }
        else
        {
            lv_canvas_fill_bg(local_canvas->canvas, lv_color_hex(0x000000), LV_OPA_COVER);
            myPoint.bg_color = lv_color_hex(0xffffff);
            local_canvas->isInvertColor = false;
        }
    }
}

void roll_change( lv_event_t * e) {
    char percentage[8];

    lv_event_code_t event_code = lv_event_get_code(e);
    if ( event_code == LV_EVENT_VALUE_CHANGED) 
    {
        uint8_t id = lv_roller_get_selected(ui_Roller2);
        lv_arc_set_value(ui_Arc2, (uint8_t)(output_nn[id]*100));
        sprintf(percentage, "%.1f%%",(output_nn[id]*100.0f));
        lv_label_set_text(ui_percentPredict, percentage);
    }
}

void ui_event_settingsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if ( event_code == LV_EVENT_CLICKED) 
    {
      slideSettings_Animation(ui_setting, 0);
      _ui_flag_modify( ui_settingsButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
      _ui_flag_modify( ui_delButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
      _ui_flag_modify( ui_predictButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
      local_canvas->isEnabled = false;
    }
}

void ui_event_applyButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if ( event_code == LV_EVENT_CLICKED) 
    {
      slideSettingsClose_Animation(ui_setting, 0);
      _ui_flag_modify( ui_settingsButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
      _ui_flag_modify( ui_delButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
      _ui_flag_modify( ui_predictButton, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
      local_canvas->isEnabled = true;
    }
}

void ui_event_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if ( event_code == LV_EVENT_CLICKED) 
    {
      predictSlideOut_Animation(ui_predictPanel, 0);
      local_canvas->isEnabled = true;
    }
}

void lvgl_component_init(handleStruct *handStruct, written_canvas *wCanvas)
{
    canvasQueue = handStruct->canvasHandle;
    NNQueue = handStruct->dataHandle;
    modelQueue = handStruct->nn_model_list;
    local_canvas = (written_canvas *)malloc(sizeof(written_canvas));
    local_canvas = wCanvas;

    // https://forum.lvgl.io/t/lvgl-draw-a-red-canvas/5024/5
    // https://forum.lvgl.io/t/how-to-change-single-pixels-in-a-monochrome-canvas/1164
    // https://forum.lvgl.io/t/draw-on-canvas-a-rect/3675/2
    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(myCANVAS_WIDTH, 
                                                         myCANVAS_HEIGHT)];
    // static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(myCANVAS_WIDTH, 
                                                        //  myCANVAS_HEIGHT)];

    lv_canvas_set_buffer(local_canvas->canvas, cbuf, myCANVAS_WIDTH, myCANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    // lv_canvas_set_buffer(local_canvas->canvas, cbuf, myCANVAS_WIDTH, myCANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    // lv_canvas_set_palette(local_canvas->canvas, 0, lv_color_hex(0x000000));
    // lv_canvas_set_palette(local_canvas->canvas, 1, lv_color_hex(0xffffff));
    //create white background canvas
    lv_canvas_fill_bg(local_canvas->canvas, lv_color_hex(0x000000), LV_OPA_COVER);

    lv_obj_set_x( local_canvas->canvas, -52 );
    lv_obj_set_y( local_canvas->canvas, 0 );
    lv_obj_set_width(local_canvas->canvas, myCANVAS_WIDTH);
    lv_obj_set_height(local_canvas->canvas, myCANVAS_HEIGHT);
    lv_obj_set_align( local_canvas->canvas, LV_ALIGN_CENTER );

    lv_draw_rect_dsc_init(&myPoint);
    myPoint.radius = 7;
    myPoint.bg_color = lv_color_hex(0xffffff);

    ui_Roller1 = lv_roller_create(ui_MainPanel);
    lv_roller_set_options( ui_Roller1, "cnn+mlp\nmlp only", LV_ROLLER_MODE_NORMAL );
    lv_obj_set_width( ui_Roller1, 86);
    lv_obj_set_height( ui_Roller1, 83);
    lv_obj_set_x( ui_Roller1, 100 );
    lv_obj_set_y( ui_Roller1, -46 );
    lv_obj_set_align( ui_Roller1, LV_ALIGN_CENTER );
    lv_obj_set_style_text_color(ui_Roller1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(ui_Roller1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Roller1, &lv_font_montserrat_10, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Roller1, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Roller1, lv_color_hex(0x31286A), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Roller1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Roller1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_border_opa(ui_Roller1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_Roller1, &lv_font_montserrat_14, LV_PART_SELECTED| LV_STATE_DEFAULT);

    //delete button assign callback init
    lv_obj_add_event_cb(ui_delButton, delete_event_cb, LV_EVENT_ALL, NULL);
    //predict button assign callback init
    lv_obj_add_event_cb(ui_predictButton, predict_event_cb, LV_EVENT_ALL, NULL);
    //adding callback for settings menu panel
    lv_obj_add_event_cb(ui_applyButton, applyBtn_event, LV_EVENT_ALL, NULL);
    //adding callback when roller2 changed
    lv_obj_add_event_cb(ui_Roller2, roll_change, LV_EVENT_ALL, NULL);

    //from squareline_ui adding event callback (move to this file)
    lv_obj_add_event_cb(ui_settingsButton, ui_event_settingsButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_applyButton, ui_event_applyButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_backButton, ui_event_backButton, LV_EVENT_ALL, NULL);
}

// used when use LV_IMG_CF_INDEXED_1BIT format
// create draw rectangle from scratch because using LV_IMG_CF_INDEXED_1BIT format.
void lv_cvs_draw_rect(lv_obj_t *canvas, uint32_t x,uint32_t y,uint32_t w,uint32_t h){
    lv_color_t c0;  
    c0.full = 1;
    uint32_t mx;
    uint32_t my;
    for( my = y; my < y+h; my++) {
        for( mx = x; mx < x+w; mx++) {
            lv_canvas_set_px(canvas, mx, my, c0);
        }
    }
}

void lvgl_show_sign(lv_indev_drv_t drv){
    ESP_ERROR_CHECK(esp_lcd_touch_read_data(drv.user_data));
    uint16_t  strength[1];
    uint8_t count = 0;

    bool touchpad_pressed = esp_lcd_touch_get_coordinates(drv.user_data, touch_x, touch_y, strength, &count, 1);
    if (touchpad_pressed && count > 0){
        uint16_t y = (uint16_t)scaled(touch_y[0],120,280,0,myCANVAS_HEIGHT-3);
        uint16_t x = (uint16_t)scaled(touch_x[0],49,215,0,myCANVAS_WIDTH-3);
        lv_canvas_draw_rect(local_canvas->canvas, myCANVAS_HEIGHT-y, x, line_point, line_point, &myPoint);
        //used when use LV_IMG_CF_INDEXED_1BIT format
        // lv_cvs_draw_rect(local_canvas->canvas, myCANVAS_HEIGHT-y, x, line_point, line_point);
    }
}