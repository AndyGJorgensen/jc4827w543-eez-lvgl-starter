/*******************************************************************************
 * GT911 capacitive touch controller (minimal I2C driver)
 ******************************************************************************/
#pragma once

#include <stdint.h>

// Reset the controller, start I2C and detect its address (0x5D / 0x14)
void gt911_init();

// Returns true when the GT911 has fresh data; *pressed / x / y then hold the
// first point in raw panel coordinates
bool gt911_poll(bool *pressed, int16_t *x, int16_t *y);
