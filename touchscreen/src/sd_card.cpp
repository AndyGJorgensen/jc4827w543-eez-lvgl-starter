#include "sd_card.h"

#include <Arduino.h>
#include <SD.h>

#include "app_config.h"
#include "board_pins.h"
#include "eez_vars.h"
#include "spi_bus.h"
#include "status_text.h"

static bool mounted = false;
static StatusText<40> status("SD: not checked");

static bool mount()
{
  SD.end();
  mounted = SD.begin(SD_CS, spi_bus(), SD_SPI_FREQ_HZ);
  if (mounted && SD.cardType() != CARD_NONE)
  {
    status.set("SD: %.1f GB card, %.1f GB free",
               SD.cardSize() / 1e9, (SD.totalBytes() - SD.usedBytes()) / 1e9);
  }
  else
  {
    mounted = false;
    status.set("SD: no card");
  }
  Serial.println(status.c_str());
  return mounted;
}

void sd_card_init()
{
  mount();
}

bool sd_card_ready()
{
  return mounted || mount();
}

/*------------------------------------------------------------------------------
 * EEZ native variables
 *----------------------------------------------------------------------------*/
EEZ_VAR_STRING_RO(sd_status, status.c_str())
