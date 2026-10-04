#include "battery.h"

#include <Arduino.h>

#include "app_config.h"
#include "board_pins.h"
#include "eez_vars.h"
#include "interval.h"
#include "status_text.h"

#define SAMPLES 16

static float volts = 0;
static int percent = 0;
static StatusText<24> text("-");

// Typical Li-ion resting voltage -> state of charge (linear between points)
static const struct { float v; int pct; } curve[] = {
  {4.20f, 100}, {4.10f, 90}, {4.00f, 80}, {3.92f, 70}, {3.85f, 60}, {3.80f, 50},
  {3.75f, 40},  {3.70f, 30}, {3.65f, 20}, {3.55f, 10}, {3.30f, 0},
};

static int voltage_to_percent(float v)
{
  const int n = sizeof(curve) / sizeof(curve[0]);
  if (v >= curve[0].v)
    return 100;
  for (int i = 1; i < n; i++)
    if (v >= curve[i].v)
      return curve[i].pct + (int)((v - curve[i].v) / (curve[i - 1].v - curve[i].v) * (curve[i - 1].pct - curve[i].pct) + 0.5f);
  return 0;
}

static float read_volts()
{
  uint32_t mv = 0;
  for (int i = 0; i < SAMPLES; i++)
    mv += analogReadMilliVolts(BAT_ADC); // factory-calibrated ADC reading
  return mv / (float)SAMPLES / 1000.0f * BAT_DIVIDER_RATIO * BATTERY_CALIBRATION;
}

static void publish()
{
  if (volts < BATTERY_EMPTY_V)
  {
    percent = 0;
    text.set("%.2f V  Empty", volts);
    return;
  }
  percent = voltage_to_percent(volts);
  text.set("%.2f V  %d%%", volts, percent);
}

void battery_init()
{
  analogSetPinAttenuation(BAT_ADC, ADC_11db); // 0..~3.1 V input range
  volts = read_volts();
  publish();
  Serial.printf("Battery: %.3f V measured -> \"%s\"\n", volts, text.c_str());
}

void battery_update()
{
  static Interval refresh(BATTERY_UPDATE_MS);
  if (!refresh.due())
    return;

  volts = volts * 0.7f + read_volts() * 0.3f; // smooth out load/ADC noise
  publish();
}

float battery_voltage()
{
  return volts;
}

int battery_percent()
{
  return percent;
}

/*------------------------------------------------------------------------------
 * EEZ native variables
 *----------------------------------------------------------------------------*/
EEZ_VAR_INT_RO(battery_percent, percent)
EEZ_VAR_STRING_RO(battery_text, text.c_str())
