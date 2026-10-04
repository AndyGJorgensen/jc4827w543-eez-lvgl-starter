#include "gui.h"

#include <Arduino.h>
#include <lvgl.h>

#include "display.h"
#include "touch.h"
#include "ui/ui.h"

static uint32_t tick_cb(void)
{
  return millis();
}

void gui_init()
{
  lv_init();
  lv_tick_set_cb(tick_cb);

  display_init();
  touch_init();

  ui_init();
}

void gui_update()
{
  lv_timer_handler();
  ui_tick();
}
