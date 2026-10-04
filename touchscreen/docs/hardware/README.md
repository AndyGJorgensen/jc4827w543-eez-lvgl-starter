# JC4827W543C hardware reference

Kept from the seller's package (the rest was removed; see the bottom of this page). Board notes,
pin findings and quirks are in [`../../BoardsInfo.md`](../../BoardsInfo.md); pins are in
[`../../include/board_pins.h`](../../include/board_pins.h).

| File | What it is |
|---|---|
| `schematic/JC4827W543-1.png` | Schematic sheet 1: power input and UART on P1, 3.3 V regulator, USB-C, **TF card (SD_Car)**, extension headers P2–P5, **battery sense divider on IO5** |
| `schematic/JC4827W543-2.png` | Schematic sheet 2: ESP32-S3 module pin nets, **LCD connector (QSPI NV3041A)**, backlight MOSFET, GT911 capacitive touch, XPT2046 resistive touch (R model), **NS4168 audio amp**, Li-ion charger |
| `JC4827W543-Specifications-EN.pdf` | Seller's spec sheet: ESP32-S3 N4R8, 480×272, interface photo |
| `mechanical/structure-*.{jpg,png}` | Board outline and dimensions (120 × 70.2 mm), for enclosures |
| `datasheets/Nsiway-NS4168.pdf` | Datasheet of the I2S class-D speaker amp (U4) |
| `vendor-demo/LvglWidgets.ino`, `touch.h` | Seller's working demo setup (Arduino_GFX `Arduino_ESP32QSPI` + `Arduino_NV3041A` + Canvas; GT911 via TouchLib; LVGL 8). Our `src/display.cpp`/`src/gt911.cpp` are based on it |
| `factory-firmware/JC4827W543C_I.bin` | Complete factory flash image (C model) with the seller's demo; useful to check the hardware |

**The schematics are the reliable pin source.** The seller's IO spreadsheet and README (removed) had
errors: SD MOSI/MISO swapped, IO5 shown as free, and an RGB panel that this board doesn't have.

## Restoring the factory demo

This **erases this project's firmware and partition table**. To go back, upload this project over USB
(`pio run -t upload --upload-port COM7`); OTA won't work until then.

```
~/.platformio/penv/Scripts/python.exe ~/.platformio/packages/tool-esptoolpy/esptool.py \
  --chip esp32s3 --port COM7 --baud 921600 write_flash --flash_mode qio --flash_freq 80m 0x0 \
  docs/hardware/factory-firmware/JC4827W543C_I.bin
```
(Seller's instructions: whole image at `0x0`, SPI mode QIO, 80 MHz.)

## Not kept

The rest of the seller's package was removed and purged from git history to keep the repository small.
To get anything else (manual, examples, flash tool, N/R model images), download the seller's full package:
**https://pan.jczn1688.com/directlink/1/HMI%20display/JC4827W543.zip**

Removed: Arduino library copies (Arduino_GFX 1.4.4, LVGL 8.3, TouchLib/GT911, ESP32-audioI2S, TFT_eSPI…),
LVGL demos/benchmark, WiFi/BLE example sketches, the getting-started manual (5.5 MB), ESP32-S3 and
AX98357 datasheets (public; the AX98357 is not on this board), the IO spreadsheet, Espressif flash tool
and Windows serial utilities, N/R model factory images, and a third-party README/PDF guide.
