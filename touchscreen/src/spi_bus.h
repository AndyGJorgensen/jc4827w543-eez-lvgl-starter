/*******************************************************************************
 * Shared SPI bus (SPI3 / HSPI) for the TF card and, on the R model, the XPT2046
 * resistive touch controller. The LCD's QSPI uses SPI2 and is separate.
 *
 * Each device uses its own chip select and SPI transactions (SPIClass locks the
 * bus per transaction, so the audio task's SD reads and touch reads can't mix).
 ******************************************************************************/
#pragma once

#include <SPI.h>

// Start the bus (safe to call more than once) and return it
SPIClass &spi_bus();
