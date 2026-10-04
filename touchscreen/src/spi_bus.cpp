#include "spi_bus.h"

#include <Arduino.h>

#include "app_config.h"
#include "board_pins.h"

SPIClass &spi_bus()
{
  static SPIClass bus(HSPI);
  static bool started = false;
  if (!started)
  {
    // Deselect every device on the bus before talking to any of them
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
#if TOUCH_TYPE == TOUCH_RESISTIVE
    pinMode(RTP_CS, OUTPUT);
    digitalWrite(RTP_CS, HIGH);
#endif
    bus.begin(SD_SCK, SD_MISO, SD_MOSI); // CS pins are driven by each device
    started = true;
  }
  return bus;
}
