# JC4827W543 ESP32-S3 4.3" touchscreen + EEZ Studio starter

A ready-to-build baseline for the **JC4827W543C** (ESP32-S3, 4.3" 480×272 IPS, capacitive touch) using
**EEZ Studio** (LVGL 9.5 with EEZ Flow) and **PlatformIO**. All of the board's hardware works out of the
box (display, touch, WiFi, OTA updates, SD card, speaker, battery monitor) so you can start designing
your own screens in EEZ Studio straight away instead of fighting the setup.

The seller's documentation for this board has several errors (see [Board gotchas](#board-gotchas)).
Everything here was checked against the schematics and on real hardware.

## What works

| Feature | Details |
|---|---|
| **Display** | NV3041A over QSPI, LVGL 9.5, correct colours, 180° flip option |
| **Touch** | GT911 capacitive (C model). XPT2046 resistive (R model) is selectable but untested |
| **WiFi** | Scan, connect with on-screen keyboard, status (SSID, IP, host name, signal, MAC), auto-reconnect |
| **Saved networks** | Last 3 networks that connected successfully, with connect/forget screen |
| **OTA updates** | Upload firmware over WiFi; on/off switch on the WIFI screen |
| **SD card** | FAT32 micro SD, size/free space shown on screen |
| **Speaker** | Plays 16-bit WAV files from the SD card through the on-board I2S amp |
| **Battery** | Li-ion voltage and percentage on the main screen, calibrated against a multimeter |
| **Settings** | Host name, OTA default, timeouts, orientation, volume and more in one file |

The included EEZ Studio project (`touchscreen/Sample.eez-project`) has four screens that use all of the
above: **Main** (battery, Settings button), **Settings** (WIFI button, test sound, SD/audio status),
**WIFI** and **Saved WiFi**. Keep them, restyle them, or delete what you don't need.

## Requirements

- JC4827W543**C** board (capacitive touch). The R (resistive) model should work with one setting change and calibration; the N (no touch) model works without touch.
- [VS Code](https://code.visualstudio.com/) with the [PlatformIO](https://platformio.org/) extension, or PlatformIO Core
- [EEZ Studio](https://github.com/eez-open/studio/releases) (tested with 0.29, project set to LVGL 9.5.0)
- A USB-C **data** cable (charge-only cables don't show up as a COM port)

## Quick start

1. **Clone** this repository and open the `touchscreen/` folder in VS Code (PlatformIO detects the project from its `platformio.ini`).
2. **Settings:** edit `touchscreen/include/app_config.h` if needed (host name, touch type, OTA default...).
3. **First upload over USB** (it also writes the OTA-capable partition table):
   ```
   pio run -d touchscreen -t upload --upload-port COM3      # your board's port
   ```
   Or use the PlatformIO **Upload** button.
4. **SD card (optional):** copy `touchscreen/sd_card_files/test.wav` to the root of a FAT32 micro SD card for the **Test Sound** button.
5. **WiFi:** Settings → WIFI → **Scan**, pick your network, type the password, **Connect**. It's remembered and reconnects at boot.
6. **Later uploads over WiFi** (OTA switch on, board connected):
   ```
   pio run -d touchscreen -e jc4827w543c_ota -t upload
   ```

## Designing your own UI

1. Open `touchscreen/Sample.eez-project` in EEZ Studio and change the screens.
2. Press **Build**. EEZ Studio writes the C code into `touchscreen/src/ui/`.
3. Upload with PlatformIO.

`src/ui/` is **generated**: EEZ Studio overwrites it on every Build, so never put your own code there.

### Connecting the UI to your code

Screens talk to the firmware through EEZ **native variables** and **native actions**:

- **Native variable**: in EEZ Studio add a global variable, tick *Native*, and bind a widget to it
  (e.g. a label's text expression). Implement it in any `src/*.cpp` file:
  ```cpp
  #include "eez_vars.h"
  #include "status_text.h"

  static StatusText<32> motor_text("Stopped");
  EEZ_VAR_STRING_RO(motor_status, motor_text.c_str())   // read-only string shown on screen

  static bool pump_on = false;
  EEZ_VAR_BOOL(pump_enabled, pump_on)                    // two-way, e.g. bound to a switch
  ```
- **Native action**: add an action with *Implementation: Native*, set a button's event handler to it, Build, then implement it:
  ```cpp
  #include "ui/actions.h"
  extern "C" void action_start_motor(lv_event_t *e) { /* ... */ }
  ```
  One action can serve several buttons: give each event handler a different *User data* value and read it with `eez_event_user_data(e)`.

Keep layout (positions, sizes, fonts) in EEZ Studio. From C, only change content and state
(`lv_label_set_text`, `lv_obj_add_flag`, `lv_obj_add_state`...), so the EEZ Studio canvas always matches
the device.

## Project layout

```
touchscreen/
├── platformio.ini          build/upload settings (USB env + OTA env)
├── Sample.eez-project      EEZ Studio project (LVGL 9.5, flow)
├── include/
│   ├── app_config.h        ← settings you're expected to change
│   ├── board_pins.h        every pin on the board, checked against the schematic
│   └── lv_conf.h           LVGL configuration
├── src/
│   ├── main.cpp            init + loop, nothing else
│   ├── gui, display, touch, gt911, xpt2046   display and touch drivers
│   ├── wifi_manager, wifi_saved, ota         networking
│   ├── spi_bus, sd_card, audio, battery      peripherals
│   ├── eez_vars.h, status_text.h, interval.h helpers for your own code
│   └── ui/                 generated by EEZ Studio (don't edit)
├── sd_card_files/          files for the micro SD card (test.wav)
├── docs/hardware/          schematics, spec sheet, dimensions, amp datasheet, factory firmware
├── BoardsInfo.md           detailed hardware notes and measurements
└── AGENTS.md, .claude/     instructions for AI coding assistants (optional)
```

## Settings (`include/app_config.h`)

| Setting | Default | What it does |
|---|---|---|
| `FLIP` | `false` | Turn the screen 180° (touch follows) |
| `LCD_INVERT_COLORS` | `true` | Must be `true` on this panel for correct colours |
| `TOUCH_TYPE` | `TOUCH_CAPACITIVE` | `TOUCH_RESISTIVE` for the R model (+ `XPT2046_*` calibration) |
| `WIFI_HOSTNAME` | `"touchscreen"` | Network/mDNS name, also the OTA target (`touchscreen.local`) |
| `WIFI_CONNECT_TIMEOUT_MS` / `WIFI_RETRY_INTERVAL_MS` | 20 s / 30 s | Connect timeout, retry interval for saved networks |
| `WIFI_SAVED_MAX` | `3` | Saved networks kept |
| `OTA_ENABLED_DEFAULT` | `true` | OTA switch position at boot |
| `OTA_PASSWORD` | `""` | Optional OTA upload password |
| `BATTERY_CALIBRATION` | `1.000` | Multimeter reading ÷ displayed voltage, if they differ |
| `BATTERY_EMPTY_V` | `3.40` | Below this the screen shows "Empty" |
| `SD_SPI_FREQ_HZ` | 20 MHz | Lower it if a card won't mount |
| `TEST_SOUND_PATH` / `AUDIO_VOLUME_PERCENT` | `/test.wav` / 60 | Test sound file and volume |

If you change `WIFI_HOSTNAME` or set `OTA_PASSWORD`, update the `[env:jc4827w543c_ota]` section of
`platformio.ini` to match.

## Board gotchas

Things that differ from the seller's documentation (details and measurements in `touchscreen/BoardsInfo.md`):

- **The display is QSPI (NV3041A), not 24-bit RGB.** The seller's README describes a different board.
- **Colours need inversion ON.** The LCD has no reset line, so it keeps its previous state across a warm
  reset. Always judge colours after unplugging power, not just after an upload.
- **SD card: MOSI is IO11 and MISO is IO13.** The seller's pin spreadsheet has them swapped.
- **IO5 is the battery sense input**, not a free GPIO, even though it's on header P2.
- **The battery divider ratio is 1.685**, not the schematic's 1.33 (a 68 kΩ resistor is fitted instead of 33 kΩ).
- **A missing battery can't be detected while USB is connected:** the charger holds the battery line at
  4.2 V, so it looks like a full battery. The charger's status pins aren't wired to the ESP32.
- **The USB-C port is the ESP32-S3's native USB** (USB-JTAG/serial), not a CH340.
- The module is an **ESP32-S3 N4R8** (4 MB flash, 8 MB OPI PSRAM), using the `min_spiffs` partition table
  (two 1.9 MB app slots for OTA).

## Troubleshooting

| Problem | Fix |
|---|---|
| Board not visible as a COM port | Use a data cable; check the board is powered |
| Colours inverted (white looks black) | Unplug power completely and plug back in; check `LCD_INVERT_COLORS true` |
| Touch lands in the wrong place | Check `FLIP` and `TOUCH_TYPE`; on the R model, calibrate `XPT2046_*` |
| SD card not detected | FAT32 format; lower `SD_SPI_FREQ_HZ` |
| OTA "No response" / "Error Uploading" | Check the WIFI screen shows OTA **Ready**, retry, or use `--upload-port <board IP>` |
| Build errors about `objects.<name>` or `action_<name>` | Run **Build** in EEZ Studio after changing the project |

## License

MIT, see [LICENSE](LICENSE). Third-party material (the seller's hardware files, the EEZ Flow runtime and
the libraries) keeps its own license, as listed at the end of the LICENSE file.

## Credits

Board: JC4827W543 by Shenzhen Jingcai Intelligent (Guition). The files in `touchscreen/docs/hardware/`
(schematics, spec sheet, drawings, factory firmware) come from the seller's package and belong to their
respective owners. The NS4168 datasheet belongs to Nsiway.

Built with [LVGL](https://lvgl.io/), [EEZ Studio](https://www.envox.eu/studio/studio-introduction/),
[GFX Library for Arduino](https://github.com/moononournation/Arduino_GFX) and the ESP32 Arduino core.
