/*******************************************************************************
 * TF (micro SD) card on the shared SPI bus (spi_bus.h; the LCD uses SPI2)
 *
 * Implements the EEZ native variable sd_status. Use the Arduino SD object
 * (SD.open(...)) for file access once sd_card_ready() is true.
 ******************************************************************************/
#pragma once

#include <stdbool.h>

// Start the SPI bus and try to mount the card
void sd_card_init();

// True when a card is mounted; tries to mount again if it was not (card inserted later)
bool sd_card_ready();
