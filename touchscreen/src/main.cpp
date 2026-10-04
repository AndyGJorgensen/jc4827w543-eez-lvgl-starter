/*******************************************************************************
 * JC4827W543C  -  ESP32-S3 + NV3041A 480x272 QSPI LCD + GT911 capacitive touch
 * LVGL 9 + EEZ Studio (flow) UI generated into src/ui
 *
 *   include/board_pins.h   all board pins
 *   include/app_config.h   user settings: host name, OTA default, FLIP, ...
 *   src/gui.*              LVGL + EEZ UI startup / update
 *   src/display.*          NV3041A panel + LVGL display
 *   src/touch.*            LVGL touch input (driver per TOUCH_TYPE)
 *   src/gt911.*            GT911 capacitive touch driver (C model)
 *   src/xpt2046.*          XPT2046 resistive touch driver (R model, untested)
 *   src/spi_bus.*          SPI3 bus shared by the SD card and XPT2046
 *   src/wifi_manager.*     WiFi scan/connect + EEZ WIFI / Saved WiFi screen actions/vars
 *   src/wifi_saved.*       last WIFI_SAVED_MAX networks that connected (NVS)
 *   src/ota.*              over-the-air updates (WIFI screen OTA toggle)
 *   src/sd_card.*          TF card on the shared SPI bus (SD library)
 *   src/audio.*            I2S speaker, WAV playback from SD (Settings "Test Sound")
 *   src/battery.*          battery voltage/percent on IO5 (Main screen)
 *   src/eez_vars.h         macros for EEZ native variables (get_var_/set_var_)
 *   src/status_text.h      StatusText<N>: on-screen text buffers
 *   src/interval.h         Interval: non-blocking periodic timer
 ******************************************************************************/
#include <Arduino.h>

#include "audio.h"
#include "battery.h"
#include "gui.h"
#include "ota.h"
#include "sd_card.h"
#include "wifi_manager.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("JC4827W543C EEZ/LVGL start");

  gui_init();
  sd_card_init();
  audio_init();
  battery_init();
  wifi_init();
  ota_init();

  Serial.println("Setup done");
}

void loop()
{
  gui_update();
  wifi_update();
  ota_update();
  battery_update();
  delay(5);
}
