/*******************************************************************************
 * XPT2046 resistive touch controller (R model) on the shared SPI bus
 * Calibration values: XPT2046_* in app_config.h
 ******************************************************************************/
#pragma once

#include <stdint.h>

// Set up the chip select / pen IRQ pins and the shared SPI bus
void xpt2046_init();

// Same contract as gt911_poll(): returns true when there is a new reading;
// *pressed / x / y then hold the touch point in screen pixels (FLIP false)
bool xpt2046_poll(bool *pressed, int16_t *x, int16_t *y);
