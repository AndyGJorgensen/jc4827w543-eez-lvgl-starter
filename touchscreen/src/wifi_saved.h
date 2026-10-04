/*******************************************************************************
 * Saved WiFi networks (NVS, most recently connected first)
 ******************************************************************************/
#pragma once

#include <stdint.h>

struct saved_network_t
{
  char ssid[33];
  char pass[65];
};

// Load the list from NVS (also migrates the old single-network keys)
void wifi_saved_load();

// Number of saved networks (0..WIFI_SAVED_MAX)
int wifi_saved_count();

// Entry i (0 = most recent), or nullptr if out of range
const saved_network_t *wifi_saved_get(int i);

// Move/insert a network to the top of the list and persist (call after a successful connect)
void wifi_saved_remember(const char *ssid, const char *pass);

// Remove entry i and persist
void wifi_saved_forget(int i);
