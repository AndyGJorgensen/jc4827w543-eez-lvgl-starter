#include "ota.h"

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include "app_config.h"
#include "eez_vars.h"
#include "gui.h"
#include "status_text.h"

static bool enabled = OTA_ENABLED_DEFAULT;
static bool running = false;
static StatusText<32> status("Off");

static void start()
{
  ArduinoOTA.begin();
  running = true;
  status.set("Ready");
  Serial.printf("OTA: ready at %s.local (%s)\n", WIFI_HOSTNAME, WiFi.localIP().toString().c_str());
}

static void stop()
{
  ArduinoOTA.end();
  running = false;
}

void ota_init()
{
  ArduinoOTA.setHostname(WIFI_HOSTNAME);
  ArduinoOTA.setPort(OTA_PORT);
  if (OTA_PASSWORD[0])
    ArduinoOTA.setPassword(OTA_PASSWORD);

  ArduinoOTA.onStart([]() {
    status.set("Updating 0%%");
    gui_update();
  });
  ArduinoOTA.onProgress([](unsigned int done, unsigned int total) {
    // The upload blocks loop(); repaint here so the screen shows progress
    static int last_pct = -1;
    int pct = total ? done * 100 / total : 0;
    if (pct != last_pct)
    {
      last_pct = pct;
      status.set("Updating %d%%", pct);
      gui_update();
    }
  });
  ArduinoOTA.onEnd([]() {
    status.set("Done, rebooting");
    gui_update();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    status.set("%s", error == OTA_AUTH_ERROR ? "Error: password" : "Error: update failed");
  });
}

void ota_update()
{
  bool connected = WiFi.status() == WL_CONNECTED;

  if (enabled && connected && !running)
    start();
  else if (running && (!enabled || !connected))
    stop();

  if (running)
    ArduinoOTA.handle();
  else
    status.set("%s", enabled ? "Waiting for WiFi" : "Off");
}

/*------------------------------------------------------------------------------
 * EEZ native variables
 *----------------------------------------------------------------------------*/
EEZ_VAR_BOOL(ota_enabled, enabled) // written by the WIFI screen OTA toggle
EEZ_VAR_STRING_RO(ota_status, status.c_str())
