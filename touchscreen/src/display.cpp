#include "display.h"

#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>

#include "app_config.h"
#include "board_pins.h"

// NV3041A over QSPI, drawn through a PSRAM canvas (as the vendor demo)
static Arduino_DataBus *bus = new Arduino_ESP32QSPI(LCD_CS, LCD_SCK, LCD_D0, LCD_D1, LCD_D2, LCD_D3);
static Arduino_GFX *panel = new Arduino_NV3041A(bus, GFX_NOT_DEFINED /* RST */, LCD_ROTATION, LCD_INVERT_COLORS /* IPS: sends INVON */);
static Arduino_Canvas *gfx = new Arduino_Canvas(SCREEN_W, SCREEN_H, panel);

static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);

  // Push the canvas to the panel once per frame
  if (lv_display_flush_is_last(disp))
    gfx->flush();

  lv_display_flush_ready(disp);
}

void display_init()
{
  if (!gfx->begin())
    Serial.println("gfx->begin() failed!");

  // No LCD reset line: re-send the inversion mode once the panel has settled so
  // the result never depends on the state left by the previous run
  delay(20);
  panel->invertDisplay(false); // false = "as configured" (IPS flag applies INVON)

  gfx->fillScreen(BLACK);
  gfx->flush();

  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);

  // Two partial render buffers (1/6 screen each) in internal RAM
  const uint32_t buf_px = SCREEN_W * 45;
  const size_t buf_bytes = buf_px * sizeof(uint16_t);
  void *buf1 = heap_caps_malloc(buf_bytes, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  void *buf2 = heap_caps_malloc(buf_bytes, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  if (!buf1 || !buf2)
  {
    Serial.println("LVGL draw buffer alloc failed, falling back to PSRAM");
    buf1 = heap_caps_malloc(buf_bytes, MALLOC_CAP_SPIRAM);
    buf2 = heap_caps_malloc(buf_bytes, MALLOC_CAP_SPIRAM);
  }

  lv_display_t *disp = lv_display_create(SCREEN_W, SCREEN_H);
  lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
  lv_display_set_flush_cb(disp, disp_flush);
  lv_display_set_buffers(disp, buf1, buf2, buf_bytes, LV_DISPLAY_RENDER_MODE_PARTIAL);
}
