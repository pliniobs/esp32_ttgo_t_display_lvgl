# TTGO T-Display LVGL Example

This project demonstrates how to initialize and control the ST7789 LCD display on the TTGO T-Display board using ESP-IDF. The main application sets up SPI communication, configures the display, and draws a bitmap image.

# Autor: Plinio Barbosa da Silva
## Linkedin: https://www.linkedin.com/in/pl%C3%ADnio-barbosa-28171072/

## Features

- SPI bus initialization for LCD communication
- ST7789 LCD panel configuration
- Backlight and reset control
- Bitmap image rendering
- Periodic serial console output

## Hardware

- TTGO T-Display (ESP32)
- ST7789 LCD (240x135 resolution)

## Pin Configuration

| Signal      | GPIO |
|-------------|------|
| MOSI        | 19   |
| MISO        | -1   |
| SCLK        | 18   |
| CS          | 5    |
| DC          | 16   |
| BL (Backlight) | 4 |
| RST         | 23   |

## Usage

1. Clone this repository.
2. Place your bitmap image data in `main/image.c`.
3. Build and flash the project using ESP-IDF:

    ```sh
    idf.py build
    idf.py flash
    ```

4. The display will show the image and print a message every second.

## File Structure

- `main/main.c`: Main application source code.
- `main/image.c`: Bitmap image data to be displayed.

## License

See LICENSE for details.
