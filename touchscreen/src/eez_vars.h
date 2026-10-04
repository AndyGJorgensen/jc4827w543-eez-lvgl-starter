/*******************************************************************************
 * Helpers for implementing EEZ native variables and actions.
 *
 * EEZ declares get_var_<name>() / set_var_<name>() for every native variable in
 * ui/vars.h (C linkage). These macros define both; read-only variables get an
 * empty setter because vars.h requires one.
 *
 *   EEZ_VAR_STRING_RO(wifi_ip, ip.c_str())        // const char *
 *   EEZ_VAR_INT_RO(battery_percent, percent)      // int32_t
 *   EEZ_VAR_BOOL(ota_enabled, enabled)            // bool, written back by the UI
 ******************************************************************************/
#pragma once

#include <lvgl.h>

#include "ui/vars.h"

#define EEZ_VAR_STRING_RO(name, expr)                       \
  extern "C" const char *get_var_##name() { return (expr); } \
  extern "C" void set_var_##name(const char *) {}

#define EEZ_VAR_INT_RO(name, expr)                       \
  extern "C" int32_t get_var_##name() { return (expr); } \
  extern "C" void set_var_##name(int32_t) {}

#define EEZ_VAR_BOOL(name, storage)                   \
  extern "C" bool get_var_##name() { return (storage); } \
  extern "C" void set_var_##name(bool value) { (storage) = value; }

// The event handler's "User data" value set in EEZ Studio (e.g. a row index)
static inline int eez_event_user_data(lv_event_t *e)
{
  return (int)(intptr_t)lv_event_get_user_data(e);
}
