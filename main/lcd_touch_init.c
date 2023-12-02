#include "lcd_touch_init.h"

static const char *TAG = "LCD_TOUCH_INIT";

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
}

/* Rotate display and touch, when rotated screen in LVGL. Called when driver parameters are updated. */
static void lvgl_port_update_callback(lv_disp_drv_t *drv)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, false);
        #if CONFIG_LCD_TOUCH_ENABLED
            // Rotate LCD touch
            esp_lcd_touch_set_mirror_y(tp, true);
            esp_lcd_touch_set_mirror_x(tp, false);
        #endif
        break;
    case LV_DISP_ROT_90:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, true);
        #if CONFIG_LCD_TOUCH_ENABLED
            // Rotate LCD touch
            esp_lcd_touch_set_mirror_y(tp, true);
            esp_lcd_touch_set_mirror_x(tp, false);
        #endif
        break;
    case LV_DISP_ROT_180:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, true);
        #if CONFIG_LCD_TOUCH_ENABLED
            // Rotate LCD touch
            esp_lcd_touch_set_mirror_y(tp, true);
            esp_lcd_touch_set_mirror_x(tp, false);
        #endif
        break;
    case LV_DISP_ROT_270:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, false);
        #if CONFIG_LCD_TOUCH_ENABLED
            // Rotate LCD touch
            esp_lcd_touch_set_mirror_y(tp, true);
            esp_lcd_touch_set_mirror_x(tp, false);
        #endif
        break;
    }
}

static void lvgl_touch_cb(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_err_t fail = esp_lcd_touch_read_data(drv->user_data);

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(drv->user_data, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0 && fail!=ESP_FAIL) {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        // printf("x->%d, y->%d \r\n",touchpad_x[0],touchpad_y[0]);
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

void lcd_and_touch_init(void *param)
{
    lcd_touch_config_t cfg = *(lcd_touch_config_t*) param;
    //hold semaphore
    xSemaphoreTakeRecursive(cfg.semaphore_handle, portMAX_DELAY);
    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    static lv_disp_drv_t disp_drv;      // contains callback functions

    // ESP_LOGI(TAG, "Turn off LCD backlight");
    // gpio_config_t bk_gpio_config = {
    //     .mode = GPIO_MODE_OUTPUT,
    //     .pin_bit_mask = 1ULL << PIN_NUM_BK_LIGHT
    // };
    // ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg0 = {
        .sclk_io_num = cfg.lcd_sclk_pin,
        .mosi_io_num = cfg.lcd_mosi_pin,
        .miso_io_num = cfg.lcd_miso_pin,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = cfg.lcd_hor_res * 80 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg0, SPI_DMA_CH_AUTO));

    spi_bus_config_t buscfg1 = {
        .sclk_io_num = cfg.touch_sclk_pin,
        .mosi_io_num = cfg.touch_mosi_pin,
        .miso_io_num = cfg.touch_miso_pin,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = cfg.lcd_hor_res * 80 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(TOUCH_HOST, &buscfg1, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = cfg.lcd_dc_pin,
        .cs_gpio_num = cfg.lcd_cs_pin,
        .pclk_hz = cfg.lcd_spi_clock,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = notify_lvgl_flush_ready,
        .user_ctx = &disp_drv,
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = cfg.lcd_rst_pin,
        .rgb_endian = LCD_RGB_ENDIAN_BGR,
        .bits_per_pixel = 16,
    };
    ESP_LOGI(TAG, "Install ILI9341 panel driver");
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_spi_config_t tp_io_config = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(cfg.touch_cs_pin);
    // Attach the TOUCH to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)TOUCH_HOST, &tp_io_config, &tp_io_handle));

    gpio_num_t pin_irq; 
    if (cfg.use_touch_irq){
        pin_irq = cfg.touch_irq_pin;
    }
    else{
        pin_irq = -1;
    }
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = cfg.lcd_hor_res,
        .y_max = cfg.lcd_ver_res,
        .rst_gpio_num = -1,
        .int_gpio_num = pin_irq,
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 1,
        },
    };

    ESP_LOGI(TAG, "Initialize touch controller XPT2046");
    ESP_ERROR_CHECK(esp_lcd_touch_new_spi_xpt2046(tp_io_handle, &tp_cfg, &cfg.touch_handle));

    if(cfg.LCD_ROTATED){
        // ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, true));
    }else{
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
    }

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    // alloc draw buffers used by LVGL
    lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);
    
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = cfg.lcd_hor_res;
    disp_drv.ver_res = cfg.lcd_ver_res;
    disp_drv.flush_cb = lvgl_flush_cb;
    if(cfg.LCD_ROTATED){
        disp_drv.rotated = LV_DISP_ROT_90;
    }else{
        disp_drv.rotated = LV_DISP_ROT_NONE;
    }
    disp_drv.drv_update_cb = lvgl_port_update_callback;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    // lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
    cfg.lvgl_handle->disp = lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));


    //static lv_indev_drv_t indev_drv;    // Input device driver (Touch)
    lv_indev_drv_init(&cfg.lvgl_handle->indev_drv);
    cfg.lvgl_handle->indev_drv.type = LV_INDEV_TYPE_POINTER;
    cfg.lvgl_handle->indev_drv.disp = cfg.lvgl_handle->disp;
    cfg.lvgl_handle->indev_drv.read_cb = lvgl_touch_cb;
    cfg.lvgl_handle->indev_drv.user_data = cfg.touch_handle;

    lv_indev_drv_register(&cfg.lvgl_handle->indev_drv);

    xSemaphoreGiveRecursive(cfg.semaphore_handle);
    ESP_LOGI(TAG, "semaphore has been given!");
    vTaskSuspend(cfg.task);
}


