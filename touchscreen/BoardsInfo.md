# JC4827W543C board notes (ESP32-S3, 4.3" 480x272, GT911 capacitive touch)

Sources: schematics, spec sheet and vendor demo in [`docs/hardware/`](docs/hardware/README.md), plus measurements on the board.

## The vendor README is wrong about the display
The seller's README (removed; in the seller package, link in docs/hardware/README.md) describes a 24-bit **RGB** panel with RGB pin/timing tables.
Those tables belong to the Sunton ESP32-4827S043, a different board. **This board uses a QSPI
panel with an NV3041A controller.** The vendor's working demo (`docs/hardware/vendor-demo/LvglWidgets.ino`) confirms it.
Ignore the README's `ESP32_4827S043` define, RGB pins, and RGB timings.

## MCU
- ESP32-S3-WROOM-1 **N4R8**: 4 MB QIO flash (flash id 0x1640EF), 8 MB **OPI** PSRAM
- PlatformIO: `board = esp32-s3-devkitc-1` + `memory_type = qio_opi`, `flash_size = 4MB`
- USB-C is the ESP32-S3 **native USB** (enumerates as "USB JTAG/serial debug unit", VID_303A&PID_1001),
  not a CH340 (despite the vendor shipping a CH340 driver). Use `-DARDUINO_USB_CDC_ON_BOOT=1` so Serial goes to USB.
- No USB device at all in Windows = charge-only cable / board switched off; a good data cable shows up immediately.

## LCD – NV3041A, QSPI, 480x272, IPS, RGB565
| Signal | GPIO |
|--------|------|
| CS     | 45 |
| SCK    | 47 |
| D0     | 21 |
| D1     | 48 |
| D2     | 40 |
| D3     | 39 |
| TE     | 0 (shared with BOOT, unused) |
| RST    | not connected (GFX_NOT_DEFINED) |
| Backlight | **1** (HIGH = on, can be PWM'd) |

Arduino_GFX: `Arduino_ESP32QSPI(45,47,21,48,40,39)` → `Arduino_NV3041A(bus, GFX_NOT_DEFINED, rot, true)`
(IPS flag **true** = INVON = correct colours, same as the vendor demo. `false` = white→black, blue→yellow.
Set via `LCD_INVERT_COLORS` in app_config.h. **The LCD has no reset line**: a warm reset/upload keeps the
panel's previous INVON/INVOFF state, which once made the wrong setting look right. Always judge colours
after a full power-off. display.cpp re-sends the inversion command after begin() for determinism.)
→ `Arduino_Canvas(480,272,panel)` (framebuffer in PSRAM; `gfx->flush()` pushes it).
With LVGL 9 no byte swap is needed (`draw16bitRGBBitmap` into the canvas).

## Touch – GT911 (I2C)
| Signal | GPIO |
|--------|------|
| SDA | 8 |
| SCL | 4 |
| INT | 3 |
| RST | 38 |
- Address 0x5D (INT held low during reset), 0x14 otherwise
- GT911 raw coordinates match the LCD at **rotation 0** (MX|MY). At rotation 2 (MADCTL = 0, image
  turned 180°) touch must be mirrored on X and Y. Confirmed on hardware by the user (an earlier note
  here had these swapped).
- `include/app_config.h` `#define FLIP true|false` selects: false = rotation 0 + raw touch,
  true = rotation 2 + touch mirrored (both verified on hardware). Rotation is done in the NV3041A (MADCTL), no CPU cost.
- Status reg 0x814E (bit7 = data ready, low nibble = touch count), first point at 0x8150, write 0 to 0x814E to clear

## Board variants (touch)
| Model | Touch | Firmware setting (`TOUCH_TYPE` in app_config.h) |
|---|---|---|
| JC4827W543**C** (ours) | GT911 capacitive, I2C | `TOUCH_CAPACITIVE`, verified |
| JC4827W543**R** | XPT2046 resistive, SPI on IO12/11/13, CS 38, IRQ 3, **shared with the TF card** | `TOUCH_RESISTIVE`, compiles, not tested on hardware |
| JC4827W543**N** | none | either |

Pins 38 and 3 are reused: GT911 RST/INT on the C model, XPT2046 CS/IRQ on the R model. That's why
`src/spi_bus.cpp` only drives IO38 as a chip select in resistive mode. The R model needs calibrating:
set `XPT2046_LOG_RAW 1`, press the screen edges, and copy the raw values into `XPT2046_RAW_*`.

## Audio – I2S amp (NS4168 / MAX98357-class) → "Speak" connector
| Signal | GPIO |
|--------|------|
| LRCLK | 2 |
| BCLK  | 42 |
| DIN   | 41 |

Driven with the ESP32 legacy I2S driver (`driver/i2s.h`, core 2.0.17): I2S_NUM_0 master TX, Philips
I2S, 16-bit stereo frames (mono WAVs are duplicated to L+R). Code: `src/audio.cpp` (WAV playback task).
Amp is an NS4168 (U4) powered from VOUT-BAT; its CTRL pin is pulled to VOUT-BAT through 1 MΩ, so it
is always enabled (no enable GPIO). Not yet verified by ear on hardware.

## TF card (SPI)
On its own SPI bus: **SPI3 / HSPI** (`SPIClass(HSPI)`), because the LCD's QSPI owns SPI2. Arduino `SD`
library, FAT32 card, `SD_SPI_FREQ_HZ` in app_config.h. Code: `src/sd_card.cpp`. Verified on hardware: 4 GB FAT32 card mounts at 20 MHz.

| Signal | GPIO |
|--------|------|
| CS   | 10 |
| MOSI | 11 (→ card CMD) |
| CLK  | 12 |
| MISO | 13 (← card DAT0) |

**The vendor IO spreadsheet is wrong here:** it labels IO11 "TF_MISO" and IO13 "TF_MOSI". The schematic
(`docs/hardware/schematic/JC4827W543-1.png`, SD_Car block) shows IO11 = MCU_MOSI and
IO13 = MCU_MISO. With them swapped the card never answers CMD0 ("Card Failed! cmd: 0x00").
The schematics in that folder (`JC4827W543-1.png`, `-2.png`) are the reliable pin reference.

## Other
- UART0: TX 43 / RX 44; UART1 header: TX 17 / RX 18
- USB D+/D-: 20/19
- Free/extension IO (headers P2–P5): 6, 7, 9, 14, 15, 16, 17, 18, 46
- **IO5 = battery voltage sense**: BAT, R26, IO5 (via R25 0R), R27 100k, GND. It is also brought out on P2,
  but it's not a free pin (the spreadsheet doesn't mention this).
  **The schematic is wrong about R26:** it says 33k (BAT = pin × 1.33), but on the board the ratio measures
  **1.685** (multimeter 4.092 V at P6 vs IO5 2.429 V; ADC raw ~2930/4095, not saturated), so R26 is ~68k.
  `BAT_DIVIDER_RATIO` in board_pins.h uses the measured value; verified on battery: meter 4.12 V, screen 4.13 V.
  With **no battery** (USB powered) the charger holds BAT at ~4.20 V (IO5 ~2.49 V), so it reads as a full
  battery. **A missing battery can't be detected on this board while USB is connected** (tested 2026-10-04):
  - Voltage: no battery ≈ 4.20–4.21 V; a full cell on the charger ≈ 4.19–4.20 V. Indistinguishable.
  - Ripple/noise on BAT (std. dev. of a fast ADC burst) follows the **charger's activity**, not battery
    presence: battery charging hard right after plug-in ~7, battery nearly full ~3.5, no battery 4.4–7.2.
    A noise-threshold detector was tried and gave inverted results.
  - The charger IC's status pins (U2 LED1–3) and VBUS are not wired to any ESP32 GPIO.
  A hardware mod (e.g. a charger status pin or VBUS divider to a free GPIO) would be needed. `src/battery.cpp` shows "<volts> Empty" below `BATTERY_EMPTY_V` (3.40 V).
- 4-pin power connector P1 also carries UART0 TX/RX (via 100R)
- Li-ion battery charger with protection, battery switch SW1
- IO35–37 not available (used by OPI PSRAM)

## Software stack that works (this project)
- PlatformIO espressif32 (Arduino core 2.0.17), `GFX Library for Arduino@1.4.9`, `lvgl@9.5.0`
- `include/lv_conf.h`: must not `#include` anything (LVGL 9 `.S` files include it)
- EEZ flow code includes `<lvgl/lvgl.h>` and `<lvgl/src/lvgl_private.h>` → build flag
  `-I"${platformio.libdeps_dir}/${this.__env__}"` makes those resolve to the PlatformIO lvgl lib
- The lvgl version in `platformio.ini` must match the version selected in EEZ Studio
- Flash layout: `min_spiffs.csv` (4MB: two 1.875MB OTA app slots, 128KB SPIFFS, NVS at 0x9000).
  `huge_app.csv` (single 3MB app) does NOT support OTA. The partition table can only be changed by a
  USB upload, never over the air.

## Pin header
All pins in `include/board_pins.h` were checked against both schematic sheets (2026-10-04).
All board pins (used and unused: LCD, GT911, XPT2046 on the R variant, TF card, I2S speaker,
BOOT, UARTs, USB, free extension IO) are defined in `include/board_pins.h`. Include that instead of
hard-coding pin numbers. Note: IO38 is GT911 RST on the C variant and XPT2046 CS on the R variant;
IO3 is GT911 INT / XPT2046 IRQ. TF card and XPT2046 share SPI on IO11/12/13.
