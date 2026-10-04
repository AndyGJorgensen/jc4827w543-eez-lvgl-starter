/*******************************************************************************
 * WiFi station: scan, connect, status for the EEZ "WIFI" screen
 *
 * Implements the EEZ native actions (wifi_scan, wifi_connect, wifi_disconnect,
 * wifi_saved_connect, wifi_saved_forget, wifi_keyboard_show, wifi_keyboard_hide)
 * and native variables (wifi_status, wifi_ssid, wifi_ip, wifi_hostname, wifi_rssi,
 * wifi_mac, saved_wifi_1..3, wifi_keyboard_visible).
 * Networks are remembered (wifi_saved) only after they connect successfully.
 ******************************************************************************/
#pragma once

// Set hostname, start station mode and connect to the most recent saved network
void wifi_init();

// Poll scan results and refresh status text; call from loop()
void wifi_update();
