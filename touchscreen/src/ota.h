/*******************************************************************************
 * Over-the-air firmware update (ArduinoOTA / espota)
 *
 * Implements the EEZ native variables ota_enabled (WIFI screen toggle) and
 * ota_status. OTA listens only while enabled AND WiFi is connected.
 ******************************************************************************/
#pragma once

// Apply OTA_ENABLED_DEFAULT; OTA starts once WiFi connects
void ota_init();

// Start/stop the listener as WiFi / the toggle change, and serve uploads; call from loop()
void ota_update();
