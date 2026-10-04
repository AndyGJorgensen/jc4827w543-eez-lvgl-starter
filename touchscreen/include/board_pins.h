/*******************************************************************************
 * JC4827W543C pin map (ESP32-S3-WROOM-1 N4R8)
 * Verified against the schematics docs/hardware/schematic/JC4827W543-1.png
 * and -2.png. The vendor IO spreadsheet has errors (SD MOSI/MISO,
 * IO5) - trust the schematics.
 ******************************************************************************/
#pragma once

/*------------------------------------------------------------------------------
 * LCD - NV3041A, 480x272, QSPI
 *----------------------------------------------------------------------------*/
#define LCD_CS   45
#define LCD_SCK  47
#define LCD_D0   21
#define LCD_D1   48
#define LCD_D2   40
#define LCD_D3   39
#define LCD_TE   0   // tearing effect out; shared with BOOT button, not used
#define LCD_RST  -1  // not connected
#define LCD_BL   1   // backlight, HIGH = on (PWM capable)

#define SCREEN_W 480
#define SCREEN_H 272

/*------------------------------------------------------------------------------
 * Capacitive touch - GT911, I2C (0x5D, or 0x14)
 *----------------------------------------------------------------------------*/
#define TOUCH_SDA 8
#define TOUCH_SCL 4
#define TOUCH_INT 3
#define TOUCH_RST 38

/*------------------------------------------------------------------------------
 * Resistive touch - XPT2046, SPI (only fitted on the "R" variant, JC4827W543R)
 * Shares the SPI bus with the TF card.
 *----------------------------------------------------------------------------*/
#define RTP_CS   38
#define RTP_CLK  12
#define RTP_DIN  11
#define RTP_DOUT 13
#define RTP_IRQ  3

/*------------------------------------------------------------------------------
 * TF (micro SD) card - SPI
 *----------------------------------------------------------------------------*/
// Per the schematic (SD_Car: IO11 MCU_MOSI -> CMD, IO13 MCU_MISO <- DAT0).
// The vendor IO spreadsheet has MOSI/MISO swapped - don't trust it for these two.
#define SD_CS   10
#define SD_MOSI 11
#define SD_SCK  12
#define SD_MISO 13

/*------------------------------------------------------------------------------
 * Speaker - I2S class-D amp (NS4168) -> "Speak" connector P7
 *----------------------------------------------------------------------------*/
#define I2S_LRCLK 2
#define I2S_BCLK  42
#define I2S_DOUT  41   // ESP32 data out -> amp DIN

/*------------------------------------------------------------------------------
 * Battery voltage sense (ADC): BAT -- R26 -- IO5 -- R27 100k -- GND (via R25 0R)
 * The schematic says R26 = 33k (ratio 1.33), but on the real board the ratio
 * measures 1.685 (multimeter 4.092 V vs IO5 2.429 V), i.e. R26 is ~68k.
 * A 4.2 V cell puts ~2.49 V on IO5. Also on header P2, so don't drive IO5
 * from the header.
 *----------------------------------------------------------------------------*/
#define BAT_ADC 5
#define BAT_DIVIDER_RATIO 1.685f   // battery volts = pin volts * ratio (measured, see above)

/*------------------------------------------------------------------------------
 * Buttons
 *----------------------------------------------------------------------------*/
#define BTN_BOOT 0   // active LOW

/*------------------------------------------------------------------------------
 * UARTs
 *----------------------------------------------------------------------------*/
#define UART0_TX 43  // also on the 4-pin power connector P1 (via 100R)
#define UART0_RX 44
#define UART1_TX 17  // "UART1" header
#define UART1_RX 18

/*------------------------------------------------------------------------------
 * Native USB (USB-C) - used by USB CDC / JTAG, do not reuse
 *----------------------------------------------------------------------------*/
#define USB_DN 19
#define USB_DP 20

/*------------------------------------------------------------------------------
 * Free GPIOs on the extension headers (P2-P5)
 *----------------------------------------------------------------------------*/
#define EXT_IO6  6
#define EXT_IO7  7
#define EXT_IO9  9
#define EXT_IO14 14
#define EXT_IO15 15
#define EXT_IO16 16
#define EXT_IO46 46   // strapping pin: keep LOW/floating at boot
// IO17 / IO18 are on the UART1 headers (P4, P5) and can also be used as GPIO
// IO5 is also on P2 but is the battery sense input (BAT_ADC), not free

/* IO35, IO36, IO37 are used by the octal PSRAM - not available */
