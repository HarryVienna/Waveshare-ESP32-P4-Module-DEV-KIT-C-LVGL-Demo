/*******************************************************************************
 * display.h - Waveshare ESP32-P4-Module-DEV-KIT-C with 10.1" DSI Display Driver
 *******************************************************************************
 *
 * Initializes and manages the complete display subsystem:
 *   - I2C bus (shared between backlight and touch)
 *   - Backlight controller (I2C address 0x45)
 *   - MIPI DSI display (JD9365, 800x1280 physical, landscape 1280x800)
 *   - GT911 capacitive touch controller
 *   - LVGL 8 integration via esp_lvgl_port
 *
 * Hardware: Waveshare 10.1-DSI-TOUCH-A on ESP32-P4 Nano
 *
 * Usage:
 *   display_init();                     // Initialize everything
 *   lv_disp_t *disp = display_get();   // Get LVGL display handle
 *   display_set_brightness(80);         // Set brightness to 80%
 *
 * IMPORTANT: Always use lvgl_port_lock(0) / lvgl_port_unlock() around
 * any lv_* calls. LVGL is not thread-safe.
 *
 ******************************************************************************/
#pragma once

#include "esp_err.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Landscape display dimensions (after 90° rotation) */
#define DISPLAY_WIDTH   1280
#define DISPLAY_HEIGHT  800

/**
 * @brief Initialize the complete display subsystem
 *
 * Performs the full initialization sequence:
 *   1. I2C bus (GPIO7=SDA, GPIO8=SCL, 400kHz)
 *   2. Backlight (I2C chip at 0x45, full brightness)
 *   3. MIPI DSI display (JD9365 with Waveshare init commands)
 *   4. GT911 touch controller (I2C address 0x5D)
 *   5. LVGL port, display registration (landscape), touch registration
 *
 * @return ESP_OK on success
 */
esp_err_t display_init(void);

/**
 * @brief Get the LVGL display handle
 *
 * Only valid after display_init() has been called.
 *
 * @return LVGL display pointer, or NULL if not initialized
 */
lv_disp_t *display_get(void);

/**
 * @brief Set display backlight brightness
 *
 * @param Brightness 0-255 (0=off, 255=full)
 * @return ESP_OK on success
 */
esp_err_t display_set_brightness(uint8_t val);

#ifdef __cplusplus
}
#endif
