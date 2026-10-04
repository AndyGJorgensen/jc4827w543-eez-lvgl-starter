/*******************************************************************************
 * Battery monitor: Li-ion voltage on IO5 (ADC1) through the 33k/100k divider
 *
 * Implements the EEZ native variables battery_percent (0..100) and
 * battery_text ("4.05 V  85%"), shown on the Main screen.
 ******************************************************************************/
#pragma once

// Configure the ADC pin and take a first reading
void battery_init();

// Re-read every BATTERY_UPDATE_MS; call from loop()
void battery_update();

// Latest smoothed battery voltage (V) and charge estimate (%)
float battery_voltage();
int battery_percent();
