// declaration in .h file:
#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "lvgl/lvgl.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_xpt2046.h"

#include "esp_timer.h"
#include "esp_log.h"

extern uint32_t DISP_BUF_SIZE;

// Using SPI2 in LCD
#define LCD_HOST  SPI2_HOST
// Using SPI3 in touch
#define TOUCH_HOST  SPI3_HOST

#define LVGL_TICK_PERIOD_MS    5

//lvgl handle structure
typedef struct 
{
    lv_disp_t *disp;
    lv_indev_drv_t indev_drv;
}lvgl_struct_t;

// create lcd and touchscreen structure
typedef struct
{
    bool LCD_ROTATED;
    bool USE_TOUCH;

    int lcd_spi_clock;

    int lcd_sclk_pin;
    int lcd_mosi_pin;
    int lcd_miso_pin;
    int lcd_dc_pin;
    int lcd_rst_pin;
    int lcd_cs_pin;
    int lcd_backlight_pin;
    bool use_backlight;

    int touch_sclk_pin;
    int touch_mosi_pin;
    int touch_miso_pin;
    int touch_cs_pin;
    int touch_irq_pin;
    bool use_touch_irq;

    int lcd_ver_res;
    int lcd_hor_res;

    esp_lcd_touch_handle_t touch_handle;
    lvgl_struct_t *lvgl_handle;

    SemaphoreHandle_t semaphore_handle;
    TaskHandle_t task;
} lcd_touch_config_t;

void lcd_and_touch_init(void *param);
#ifdef __cplusplus
}
#endif