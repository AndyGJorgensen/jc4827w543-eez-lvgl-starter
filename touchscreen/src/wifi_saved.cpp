#include "wifi_saved.h"

#include <Arduino.h>
#include <Preferences.h>

#include "app_config.h"

#define NVS_NAMESPACE "wifi"

static saved_network_t list[WIFI_SAVED_MAX];
static int count = 0;

// Write "<name><i>" = value, or remove it when value is null (only if present: avoids NVS error logs)
static void put_or_remove(Preferences &prefs, const char *name, int i, const char *value)
{
  char key[8];
  snprintf(key, sizeof(key), "%s%d", name, i);
  if (value)
    prefs.putString(key, value);
  else if (prefs.isKey(key))
    prefs.remove(key);
}

static void persist()
{
  Preferences prefs;
  prefs.begin(NVS_NAMESPACE, false);
  prefs.putUChar("count", count);
  for (int i = 0; i < WIFI_SAVED_MAX; i++)
  {
    put_or_remove(prefs, "ssid", i, i < count ? list[i].ssid : nullptr);
    put_or_remove(prefs, "pass", i, i < count ? list[i].pass : nullptr);
  }
  prefs.end();
}

void wifi_saved_load()
{
  Preferences prefs;
  prefs.begin(NVS_NAMESPACE, false);

  count = 0;
  int stored = prefs.getUChar("count", 0);
  char key[8];
  for (int i = 0; i < stored && count < WIFI_SAVED_MAX; i++)
  {
    snprintf(key, sizeof(key), "ssid%d", i);
    prefs.getString(key, list[count].ssid, sizeof(list[0].ssid));
    snprintf(key, sizeof(key), "pass%d", i);
    prefs.getString(key, list[count].pass, sizeof(list[0].pass));
    if (list[count].ssid[0])
      count++;
  }

  // Older firmware kept a single network under "ssid"/"pass"
  bool migrate = prefs.isKey("ssid");
  if (migrate)
  {
    char ssid[33] = "", pass[65] = "";
    prefs.getString("ssid", ssid, sizeof(ssid));
    prefs.getString("pass", pass, sizeof(pass));
    prefs.remove("ssid");
    prefs.remove("pass");
    prefs.end();
    if (ssid[0])
      wifi_saved_remember(ssid, pass);
    return;
  }
  prefs.end();
}

int wifi_saved_count()
{
  return count;
}

const saved_network_t *wifi_saved_get(int i)
{
  return (i >= 0 && i < count) ? &list[i] : nullptr;
}

void wifi_saved_remember(const char *ssid, const char *pass)
{
  saved_network_t entry;
  snprintf(entry.ssid, sizeof(entry.ssid), "%s", ssid);
  snprintf(entry.pass, sizeof(entry.pass), "%s", pass);

  // Drop an existing entry for this SSID, then shift everything down one
  int existing = count;
  for (int i = 0; i < count; i++)
    if (strcmp(list[i].ssid, ssid) == 0)
      existing = i;
  int last = (existing < count) ? existing : min(count, WIFI_SAVED_MAX - 1);
  for (int i = last; i > 0; i--)
    list[i] = list[i - 1];
  list[0] = entry;
  if (existing == count && count < WIFI_SAVED_MAX)
    count++;

  persist();
}

void wifi_saved_forget(int i)
{
  if (i < 0 || i >= count)
    return;
  for (int j = i; j < count - 1; j++)
    list[j] = list[j + 1];
  count--;
  persist();
}
