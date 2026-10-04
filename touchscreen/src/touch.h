/*******************************************************************************
 * LVGL touch input: GT911 (C model) or XPT2046 (R model) per TOUCH_TYPE,
 * mapped to the screen orientation in app_config.h
 ******************************************************************************/
#pragma once

// Start the touch controller and register the LVGL pointer input. Call after lv_init().
void touch_init();
