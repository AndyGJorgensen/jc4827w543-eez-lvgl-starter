#include "wifi_manager.h"

#include <Arduino.h>
#include <WiFi.h>
#include <lvgl.h>

#include "app_config.h"
#include "eez_vars.h"
#include "interval.h"
#include "status_text.h"
#include "wifi_saved.h"
#include "ui/actions.h"
#include "ui/screens.h"

#define MAX_SCAN_RESULTS 20
#define STATUS_PERIOD_MS 500

// Scan results shown in the WIFI screen dropdown
static char scan_ssids[MAX_SCAN_RESULTS][33];
static int scan_count = 0;
static bool scanning = false;

// Current connection attempt
static char attempt_ssid[33] = "";
static char attempt_pass[65] = "";
static bool connecting = false;
static bool remembered = false;       // attempt saved to the list once it got an IP
static uint32_t attempt_started = 0;

// Auto-connect to saved networks
static bool auto_connect = true;      // off after Disconnect, on again after any Connect
static int next_saved = 0;            // saved network to try next

static const char *status_message = nullptr; // shown instead of "Disconnected"

// Text shown on the WIFI / Saved WiFi screens (EEZ native variables, bottom of file)
static StatusText<32> status("Disconnected");
static StatusText<33> ssid_text("-");
static StatusText<16> ip_text("-");
static StatusText<24> rssi_text("-");
static StatusText<18> mac_text("-");
static StatusText<48> saved_text[WIFI_SAVED_MAX];
static bool keyboard_visible = false;

/*------------------------------------------------------------------------------
 * Helpers
 *----------------------------------------------------------------------------*/
static const char *signal_quality(int rssi)
{
  if (rssi >= -55) return "Excellent";
  if (rssi >= -67) return "Good";
  if (rssi >= -75) return "Fair";
  return "Weak";
}

static void start_connect(const char *ssid, const char *pass)
{
  snprintf(attempt_ssid, sizeof(attempt_ssid), "%s", ssid);
  snprintf(attempt_pass, sizeof(attempt_pass), "%s", pass);

  // Only drop an existing link; a disconnect right before begin() can cancel the new attempt
  if (WiFi.status() == WL_CONNECTED)
    WiFi.disconnect();
  WiFi.begin(attempt_ssid, attempt_pass);

  connecting = true;
  remembered = false;
  attempt_started = millis();
  status_message = nullptr;
  Serial.printf("WiFi: connecting to \"%s\"\n", ssid);
}

static void try_next_saved()
{
  int n = wifi_saved_count();
  if (n == 0)
    return;
  next_saved %= n;
  const saved_network_t *net = wifi_saved_get(next_saved++);
  start_connect(net->ssid, net->pass);
}

static void refresh_saved_list()
{
  bool connected = WiFi.status() == WL_CONNECTED;
  for (int i = 0; i < WIFI_SAVED_MAX; i++)
  {
    const saved_network_t *net = wifi_saved_get(i);
    if (!net)
      saved_text[i].set("(empty)");
    else if (connected && WiFi.SSID() == net->ssid)
      saved_text[i].set("%s (connected)", net->ssid);
    else
      saved_text[i].set("%s", net->ssid);
  }
}

static void refresh_status()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (connecting && !remembered)
    {
      wifi_saved_remember(attempt_ssid, attempt_pass); // only networks that really work
      remembered = true;
      next_saved = 0; // it is now entry 0: retry it first if the link drops
      Serial.printf("WiFi: connected, IP %s\n", WiFi.localIP().toString().c_str());
    }
    connecting = false;
    status_message = nullptr;

    status.set("Connected");
    ssid_text.set("%s", WiFi.SSID().c_str());
    ip_text.set("%s", WiFi.localIP().toString().c_str());
    int rssi = WiFi.RSSI();
    rssi_text.set("%d dBm %s", rssi, signal_quality(rssi));
  }
  else
  {
    if (connecting && millis() - attempt_started > WIFI_CONNECT_TIMEOUT_MS)
    {
      connecting = false;
      WiFi.disconnect();
      status_message = "Connect failed";
      Serial.printf("WiFi: could not connect to \"%s\"\n", attempt_ssid);
    }

    if (scanning)
      status.set("Scanning...");
    else if (connecting)
      status.set("Connecting...");
    else
      status.set("%s", status_message ? status_message : "Disconnected");

    ssid_text.set("-");
    ip_text.set("-");
    rssi_text.set("-");
  }

  refresh_saved_list();
}

static void publish_scan_results(int n)
{
  // Unique, non-hidden SSIDs, strongest first (scan results are sorted by RSSI)
  scan_count = 0;
  String options;
  for (int i = 0; i < n && scan_count < MAX_SCAN_RESULTS; i++)
  {
    String ssid = WiFi.SSID(i);
    if (ssid.length() == 0)
      continue;

    bool dup = false;
    for (int j = 0; j < scan_count && !dup; j++)
      dup = ssid.equals(scan_ssids[j]);
    if (dup)
      continue;

    snprintf(scan_ssids[scan_count], sizeof(scan_ssids[0]), "%s", ssid.c_str());
    if (scan_count > 0)
      options += "\n";
    options += ssid;
    if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
      options += "  (open)";
    options += "  ";
    options += WiFi.RSSI(i);
    scan_count++;
  }
  WiFi.scanDelete();

  lv_dropdown_set_options(objects.wifi_network_dd, scan_count ? options.c_str() : "No networks found");
  lv_dropdown_set_selected(objects.wifi_network_dd, 0);
  status_message = scan_count ? nullptr : "No networks found";
}

/*------------------------------------------------------------------------------
 * Public
 *----------------------------------------------------------------------------*/
void wifi_init()
{
  WiFi.persistent(false);          // credentials live in wifi_saved, not the driver's NVS
  WiFi.setHostname(WIFI_HOSTNAME); // must be set before the interface starts
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);

  mac_text.set("%s", WiFi.macAddress().c_str());

  wifi_saved_load();
  try_next_saved();
  refresh_status();
}

void wifi_update()
{
  if (scanning)
  {
    int n = WiFi.scanComplete();
    if (n >= 0)
    {
      scanning = false;
      publish_scan_results(n);
    }
    else if (n == WIFI_SCAN_FAILED)
    {
      scanning = false;
      status_message = "Scan failed";
    }
  }

  // Cycle through saved networks while disconnected (router rebooting, out of range...)
  if (auto_connect && !connecting && !scanning && WiFi.status() != WL_CONNECTED &&
      millis() - attempt_started >= WIFI_RETRY_INTERVAL_MS)
    try_next_saved();

  static Interval refresh(STATUS_PERIOD_MS);
  if (refresh.due())
    refresh_status();
}

/*------------------------------------------------------------------------------
 * EEZ native actions
 *----------------------------------------------------------------------------*/
extern "C" void action_wifi_scan(lv_event_t *e)
{
  if (scanning)
    return;
  WiFi.scanDelete();
  if (WiFi.scanNetworks(true /* async */) == WIFI_SCAN_FAILED)
  {
    status_message = "Scan failed";
    return;
  }
  scanning = true;
  refresh_status();
}

extern "C" void action_wifi_connect(lv_event_t *e)
{
  keyboard_visible = false;

  uint32_t sel = lv_dropdown_get_selected(objects.wifi_network_dd);
  if (sel >= (uint32_t)scan_count)
  {
    status_message = "Scan first";
    refresh_status();
    return;
  }

  auto_connect = true;
  start_connect(scan_ssids[sel], lv_textarea_get_text(objects.wifi_password));
  refresh_status();
}

extern "C" void action_wifi_disconnect(lv_event_t *e)
{
  connecting = false;
  auto_connect = false;
  WiFi.disconnect();
  status_message = nullptr;
  refresh_status();
}

// Saved WiFi screen: event userData = row (0 = most recent)
extern "C" void action_wifi_saved_connect(lv_event_t *e)
{
  const saved_network_t *net = wifi_saved_get(eez_event_user_data(e));
  if (!net)
    return;
  auto_connect = true;
  start_connect(net->ssid, net->pass);
  refresh_status();
}

extern "C" void action_wifi_saved_forget(lv_event_t *e)
{
  int row = eez_event_user_data(e);
  const saved_network_t *net = wifi_saved_get(row);
  if (!net)
    return;
  if (WiFi.status() == WL_CONNECTED && WiFi.SSID() == net->ssid)
  {
    auto_connect = false; // don't jump straight back onto the network just forgotten
    WiFi.disconnect();
  }
  wifi_saved_forget(row);
  refresh_status();
}

extern "C" void action_wifi_keyboard_show(lv_event_t *e)
{
  keyboard_visible = true;
}

extern "C" void action_wifi_keyboard_hide(lv_event_t *e)
{
  keyboard_visible = false;
}

/*------------------------------------------------------------------------------
 * EEZ native variables
 *----------------------------------------------------------------------------*/
EEZ_VAR_STRING_RO(wifi_status, status.c_str())
EEZ_VAR_STRING_RO(wifi_ssid, ssid_text.c_str())
EEZ_VAR_STRING_RO(wifi_ip, ip_text.c_str())
EEZ_VAR_STRING_RO(wifi_hostname, WIFI_HOSTNAME)
EEZ_VAR_STRING_RO(wifi_rssi, rssi_text.c_str())
EEZ_VAR_STRING_RO(wifi_mac, mac_text.c_str())
EEZ_VAR_STRING_RO(saved_wifi_1, saved_text[0].c_str())
EEZ_VAR_STRING_RO(saved_wifi_2, saved_text[1].c_str())
EEZ_VAR_STRING_RO(saved_wifi_3, saved_text[2].c_str())
EEZ_VAR_BOOL(wifi_keyboard_visible, keyboard_visible)
