#include "touch.h"

#include <Arduino.h>
#include <lvgl.h>

#include "app_config.h"
#include "board_pins.h"

// Touch controller chosen by TOUCH_TYPE in app_config.h; both report screen pixels (FLIP false)
#if TOUCH_TYPE == TOUCH_RESISTIVE
#include "xpt2046.h"
#define touch_hw_init xpt2046_init
#define touch_hw_poll xpt2046_poll
#elif TOUCH_TYPE == TOUCH_CAPACITIVE
#include "gt911.h"
#define touch_hw_init gt911_init
#define touch_hw_poll gt911_poll
#else
#error "TOUCH_TYPE in app_config.h must be TOUCH_CAPACITIVE or TOUCH_RESISTIVE"
#endif

static void touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  static int16_t last_x = 0, last_y = 0;
  static bool last_pressed = false;
  int16_t x, y;

  // Only update state when the controller has fresh data; otherwise keep last state
  if (touch_hw_poll(&last_pressed, &x, &y))
  {
    if (last_pressed)
    {
      last_x = constrain(x, 0, SCREEN_W - 1);
      last_y = constrain(y, 0, SCREEN_H - 1);
#if TOUCH_FLIP_X
      last_x = SCREEN_W - 1 - last_x;
#endif
#if TOUCH_FLIP_Y
      last_y = SCREEN_H - 1 - last_y;
#endif
    }
  }

  data->point.x = last_x;
  data->point.y = last_y;
  data->state = last_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

void touch_init()
{
  touch_hw_init();

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touch_read);
}
