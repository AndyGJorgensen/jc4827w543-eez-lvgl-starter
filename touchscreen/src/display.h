/*******************************************************************************
 * NV3041A QSPI LCD + LVGL display driver
 ******************************************************************************/
#pragma once

// Start the panel, turn on the backlight and register the LVGL display.
// Call after lv_init().
void display_init();
