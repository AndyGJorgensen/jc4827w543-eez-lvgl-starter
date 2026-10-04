/*******************************************************************************
 * Project settings - the ONE place for values you are expected to change
 * (host name, defaults, timeouts, orientation...). Code elsewhere reads these;
 * don't hard-code such values in other files.
 *
 * Sections: Display, WiFi, OTA, Battery, SD card, Audio
 * (Pins are in board_pins.h; LVGL options in lv_conf.h.)
 ******************************************************************************/
#pragma once

/*==============================================================================
 * Display
 *============================================================================*/

/*------------------------------------------------------------------------------
 * Screen orientation
 *   false = panel rotation 0, raw touch coordinates
 *   true  = turned 180 degrees: panel rotation 2, touch mirrored on X and Y
 *   (both verified on hardware)
 *----------------------------------------------------------------------------*/
#define FLIP false

#if FLIP
#define LCD_ROTATION 2
#define TOUCH_FLIP_X 1
#define TOUCH_FLIP_Y 1
#else
#define LCD_ROTATION 0
#define TOUCH_FLIP_X 0
#define TOUCH_FLIP_Y 0
#endif

/*------------------------------------------------------------------------------
 * Touch panel type: match the board model (sticker / product name)
 *   JC4827W543C -> TOUCH_CAPACITIVE (GT911, I2C)          verified on hardware
 *   JC4827W543R -> TOUCH_RESISTIVE  (XPT2046, SPI shared with the SD card)
 *                  not yet tested on hardware: calibrate with the values below
 *   JC4827W543N -> no touch panel: either setting works, touch just stays idle
 *----------------------------------------------------------------------------*/
#define TOUCH_CAPACITIVE 0
#define TOUCH_RESISTIVE  1
#define TOUCH_TYPE TOUCH_CAPACITIVE

// Resistive (XPT2046) calibration, in raw 12-bit ADC units at FLIP false.
// To calibrate: set XPT2046_LOG_RAW 1, upload, watch the serial monitor while
// pressing each screen edge, and copy the readings here. A "left" value larger
// than "right" (or "top" > "bottom") flips that axis.
#define XPT2046_RAW_LEFT    300
#define XPT2046_RAW_RIGHT   3800
#define XPT2046_RAW_TOP     300
#define XPT2046_RAW_BOTTOM  3800
#define XPT2046_SWAP_XY     0         // 1 if horizontal finger moves change the Y reading
#define XPT2046_PRESSURE_MIN 300      // ignore lighter touches (raw pressure, higher = harder)
#define XPT2046_LOG_RAW     0         // 1 = print raw x/y/pressure on serial for calibration

/*------------------------------------------------------------------------------
 * LCD colour inversion (NV3041A INVON/INVOFF)
 *   true  = inversion ON  -> correct colours on this IPS panel (verified after a cold power-up)
 *   false = inversion OFF -> white shows black, blue shows yellow
 * The panel has no reset line, so a warm reset keeps the last state: always
 * judge colours after unplugging power, not just after an upload.
 *----------------------------------------------------------------------------*/
#define LCD_INVERT_COLORS true

/*------------------------------------------------------------------------------
 * WiFi
 *----------------------------------------------------------------------------*/
// Network name of this device (router client list, mDNS "<name>.local", OTA target).
// If you change it, also change upload_port in platformio.ini [env:jc4827w543c_ota].
#define WIFI_HOSTNAME "touchscreen"

#define WIFI_CONNECT_TIMEOUT_MS 20000   // give up on a connect attempt after this long
#define WIFI_RETRY_INTERVAL_MS  30000   // while disconnected, try the next saved network this often
#define WIFI_SAVED_MAX          3       // saved networks kept (Saved WiFi screen shows this many rows)

/*------------------------------------------------------------------------------
 * OTA (over-the-air firmware update)
 *----------------------------------------------------------------------------*/
// State of the WIFI screen's OTA toggle at every boot (the toggle is not saved)
#define OTA_ENABLED_DEFAULT true

// Password required to upload over the air; "" = no password.
// If you set one, also add it to upload_flags in platformio.ini [env:jc4827w543c_ota].
#define OTA_PASSWORD ""

#define OTA_PORT 3232

/*------------------------------------------------------------------------------
 * Battery monitor (IO5 via 33k/100k divider, see board_pins.h)
 *----------------------------------------------------------------------------*/
#define BATTERY_UPDATE_MS    2000     // how often the Main screen battery reading refreshes
#define BATTERY_CALIBRATION  1.000f   // multiply reading; = multimeter volts / shown volts
// Below this the screen shows "<volts> Empty" instead of a percentage.
// Note: on USB with NO battery fitted the charger holds BAT at ~4.20 V, so the screen shows
// a full battery. A missing battery can't be detected on this board (see BoardsInfo.md).
#define BATTERY_EMPTY_V      3.40f

/*------------------------------------------------------------------------------
 * SD card
 *----------------------------------------------------------------------------*/
#define SD_SPI_FREQ_HZ 20000000       // lower (e.g. 4000000) if a card fails to mount

/*------------------------------------------------------------------------------
 * Audio (I2S amp -> "Speak" connector)
 *----------------------------------------------------------------------------*/
// WAV played by the Settings screen "Test Sound" button (16-bit PCM, mono or stereo, any rate)
#define TEST_SOUND_PATH "/test.wav"
#define AUDIO_VOLUME_PERCENT 60       // 0..100, software volume applied to WAV samples
