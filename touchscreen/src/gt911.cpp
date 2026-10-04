#include "gt911.h"

#include <Arduino.h>
#include <Wire.h>

#include "board_pins.h"

#define GT911_REG_PRODUCT_ID 0x8140
#define GT911_REG_STATUS     0x814E
#define GT911_REG_POINT1     0x8150

static uint8_t gt911_addr = 0x5D;

static bool gt911_read(uint16_t reg, uint8_t *buf, uint8_t len)
{
  Wire.beginTransmission(gt911_addr);
  Wire.write(reg >> 8);
  Wire.write(reg & 0xFF);
  if (Wire.endTransmission() != 0)
    return false;
  if (Wire.requestFrom(gt911_addr, len) != len)
    return false;
  for (uint8_t i = 0; i < len; i++)
    buf[i] = Wire.read();
  return true;
}

static void gt911_write(uint16_t reg, uint8_t val)
{
  Wire.beginTransmission(gt911_addr);
  Wire.write(reg >> 8);
  Wire.write(reg & 0xFF);
  Wire.write(val);
  Wire.endTransmission();
}

static bool gt911_probe(uint8_t addr)
{
  Wire.beginTransmission(addr);
  return Wire.endTransmission() == 0;
}

void gt911_init()
{
  // Reset with INT held low -> selects I2C address 0x5D
  pinMode(TOUCH_INT, OUTPUT);
  pinMode(TOUCH_RST, OUTPUT);
  digitalWrite(TOUCH_INT, LOW);
  digitalWrite(TOUCH_RST, LOW);
  delay(20);
  digitalWrite(TOUCH_RST, HIGH);
  delay(60);
  pinMode(TOUCH_INT, INPUT);
  delay(50);

  Wire.begin(TOUCH_SDA, TOUCH_SCL, 400000);

  if (gt911_probe(0x5D))
    gt911_addr = 0x5D;
  else if (gt911_probe(0x14))
    gt911_addr = 0x14;
  else
    Serial.println("GT911 not found on I2C!");

  uint8_t id[4] = {0};
  gt911_read(GT911_REG_PRODUCT_ID, id, 4);
  Serial.printf("GT911 @0x%02X id=%c%c%c%c\n", gt911_addr, id[0], id[1], id[2], id[3]);
}

bool gt911_poll(bool *pressed, int16_t *x, int16_t *y)
{
  uint8_t status;
  if (!gt911_read(GT911_REG_STATUS, &status, 1) || !(status & 0x80)) // buffer not ready
    return false;

  uint8_t touches = status & 0x0F;
  uint8_t p[4];
  *pressed = touches > 0 && touches <= 5 && gt911_read(GT911_REG_POINT1, p, 4);
  if (*pressed)
  {
    *x = p[0] | (p[1] << 8);
    *y = p[2] | (p[3] << 8);
  }
  gt911_write(GT911_REG_STATUS, 0); // clear status
  return true;
}
