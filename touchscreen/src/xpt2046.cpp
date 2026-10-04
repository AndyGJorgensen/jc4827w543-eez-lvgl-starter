#include "xpt2046.h"

#include <Arduino.h>

#include "app_config.h"
#include "board_pins.h"
#include "spi_bus.h"

// Control bytes: start bit, channel, 12-bit differential mode; low bits = power mode
#define CMD_X  0xD1   // X position, ADC kept on between conversions
#define CMD_Y  0x91   // Y position
#define CMD_Z1 0xB1   // pressure 1
#define CMD_Z2 0xC1   // pressure 2
#define CMD_PD 0xD0   // last read: power down and re-enable the pen IRQ

#define SPI_HZ  2000000   // XPT2046 max is ~2.5 MHz
#define SAMPLES 4

static uint16_t read12(SPIClass &spi, uint8_t cmd)
{
  spi.transfer(cmd);
  return spi.transfer16(0) >> 3; // 12-bit result, MSB first after one busy bit
}

static int16_t to_screen(int32_t raw, int32_t raw_lo, int32_t raw_hi, int32_t size)
{
  return constrain((raw - raw_lo) * (size - 1) / (raw_hi - raw_lo), 0, size - 1);
}

void xpt2046_init()
{
  pinMode(RTP_IRQ, INPUT); // active LOW while pressed (10k pull-up on the board)
  spi_bus();               // starts the bus and deselects RTP_CS
}

bool xpt2046_poll(bool *pressed, int16_t *x, int16_t *y)
{
  if (digitalRead(RTP_IRQ) == HIGH) // pen up: no need to touch the bus
  {
    *pressed = false;
    return true;
  }

  SPIClass &spi = spi_bus();
  spi.beginTransaction(SPISettings(SPI_HZ, MSBFIRST, SPI_MODE0));
  digitalWrite(RTP_CS, LOW);

  int32_t z = read12(spi, CMD_Z1) + 4095 - read12(spi, CMD_Z2);
  int32_t rx = 0, ry = 0;
  read12(spi, CMD_X); // first conversion after switching channels is noisy
  for (int i = 0; i < SAMPLES; i++)
  {
    rx += read12(spi, CMD_X);
    ry += read12(spi, CMD_Y);
  }
  read12(spi, CMD_PD);

  digitalWrite(RTP_CS, HIGH);
  spi.endTransaction();

  rx /= SAMPLES;
  ry /= SAMPLES;
#if XPT2046_SWAP_XY
  int32_t t = rx; rx = ry; ry = t;
#endif
#if XPT2046_LOG_RAW
  Serial.printf("XPT2046 raw x=%ld y=%ld pressure=%ld\n", (long)rx, (long)ry, (long)z);
#endif

  *pressed = z >= XPT2046_PRESSURE_MIN;
  if (*pressed)
  {
    *x = to_screen(rx, XPT2046_RAW_LEFT, XPT2046_RAW_RIGHT, SCREEN_W);
    *y = to_screen(ry, XPT2046_RAW_TOP, XPT2046_RAW_BOTTOM, SCREEN_H);
  }
  return true;
}
