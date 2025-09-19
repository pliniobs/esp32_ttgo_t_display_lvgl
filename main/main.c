#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "esp_system.h"
#include "esp_lcd_types.h"
#include "esp_lcd_io_spi.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_st7789.h"
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "image.c"


#define LCD_NUM_NC -1
#define LCD_PIN_NUM_MOSI 19
#define LCD_PIN_NUM_MISO -1
#define LCD_PIN_NUM_SCLK 18
#define LCD_PIN_NUM_CS 5
#define LCD_PIN_NUM_DC 16
#define LCD_PIN_NUM_BL 4
#define LCD_PIN_NUM_RST 23

#define LCD_PIXEL_CLOCK_HZ (20000000) // 20 MHz
#define LCD_CMD_BITS 8
#define LCD_PARAM_BITS 8

#define LCD_H_RES 135
#define LCD_V_RES 240
#define LCD_SPI_HOST SPI2_HOST

void app_main(void)
{
    gpio_set_direction(LCD_PIN_NUM_BL, GPIO_MODE_OUTPUT);
    gpio_set_level(LCD_PIN_NUM_BL, 1); // Turn on the backlight

    spi_bus_config_t buscfg = {
        .sclk_io_num = LCD_PIN_NUM_SCLK,
        .mosi_io_num = LCD_PIN_NUM_MOSI,
        .miso_io_num = LCD_PIN_NUM_MISO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_H_RES * LCD_V_RES * sizeof(uint16_t), // transfer 80 lines of pixels (assume pixel is RGB565) at most in one SPI transaction
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO)); // Enable the DMA feature
    
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_PIN_NUM_DC, // Data/Command control pin
        .cs_gpio_num = LCD_PIN_NUM_CS, // Chip select pin
        .pclk_hz = LCD_PIXEL_CLOCK_HZ, // Pixel clock
        .lcd_cmd_bits = LCD_CMD_BITS, // Command bits
        .lcd_param_bits = LCD_PARAM_BITS, // Parameter bits
        .spi_mode = 0, // SPI mode 0
        .trans_queue_depth = 10, // Transaction queue depth
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_SPI_HOST, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .data_endian = LCD_RGB_DATA_ENDIAN_LITTLE, // Data endian
        .reset_gpio_num = LCD_PIN_NUM_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    // Create LCD panel handle for ST7789, with the SPI IO device handle
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_disp_on_off(panel_handle, true);
    esp_lcd_panel_set_gap(panel_handle, 40, 52); // The gap is 25 pixels on the left and 52 pixels on the top
    
    
    esp_lcd_panel_mirror(panel_handle, false, true);
    esp_lcd_panel_invert_color(panel_handle, true);


    esp_lcd_panel_swap_xy(panel_handle, true); // Swap X and Y axis
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 240, 135, image);

    while(true) {
        printf("Hello my balls!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}   