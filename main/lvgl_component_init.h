// declaration in .h file:
#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "esp_log.h"
#include "esp_lcd_touch.h"
#include "lvgl/lvgl.h"
#include "ui.h"

#define myCANVAS_WIDTH      180
#define myCANVAS_HEIGHT     180
#define DOWNSIZED_WIDTH     28
#define DOWNSIZED_HEIGHT    28

typedef struct{
    lv_obj_t *canvas;
    bool isInvertColor;
    bool isEnabled;
}written_canvas;

typedef struct{
    QueueHandle_t canvasHandle;
    QueueHandle_t dataHandle;
    QueueHandle_t nn_model_list;
} handleStruct;

typedef struct{
    uint8_t status;
    float dataReceived[12];
} nnReceived;

extern lv_obj_t *ui_Roller1;

void lvgl_component_init(handleStruct *handStruct, written_canvas *wCanvas);
void lvgl_show_sign(lv_indev_drv_t drv);
nnReceived receive_nn_data(void);

// Function to downsample an image
void downsampleImage(uint8_t originalImage[myCANVAS_HEIGHT][myCANVAS_WIDTH], uint8_t downsampledImage[DOWNSIZED_HEIGHT][DOWNSIZED_WIDTH]);

#ifdef __cplusplus
}
#endif