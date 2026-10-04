/*******************************************************************************
 * Non-blocking periodic timer for loop()-driven updates.
 *
 *   static Interval refresh(500);
 *   if (refresh.due()) { ... }   // true at most once every 500 ms
 ******************************************************************************/
#pragma once

#include <Arduino.h>

class Interval
{
public:
  explicit Interval(uint32_t period_ms) : period_(period_ms) {}

  // True (and restarts the period) when at least period_ms has passed since the last true
  bool due()
  {
    uint32_t now = millis();
    if (now - last_ < period_)
      return false;
    last_ = now;
    return true;
  }

private:
  uint32_t period_;
  uint32_t last_ = 0;
};
