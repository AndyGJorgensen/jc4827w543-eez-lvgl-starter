/*******************************************************************************
 * GUI: LVGL + display + touch + EEZ Studio UI (src/ui)
 ******************************************************************************/
#pragma once

// Bring up LVGL, the display, touch and the EEZ UI
void gui_init();

// Run LVGL timers and the EEZ flow; call from loop()
void gui_update();
