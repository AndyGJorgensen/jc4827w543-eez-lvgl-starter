/*******************************************************************************
 * Fixed-size text buffer for values shown on screen (EEZ native string vars).
 * Always NUL-terminated; text longer than N-1 characters is cut off.
 *
 *   static StatusText<32> status("Off");
 *   status.set("Updating %d%%", pct);
 *   EEZ_VAR_STRING_RO(ota_status, status.c_str())
 ******************************************************************************/
#pragma once

#include <stdarg.h>
#include <stdio.h>

template <size_t N>
class StatusText
{
public:
  explicit StatusText(const char *initial = "") { set("%s", initial); }

  void set(const char *fmt, ...) __attribute__((format(printf, 2, 3)))
  {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf_, N, fmt, args);
    va_end(args);
  }

  const char *c_str() const { return buf_; }

private:
  char buf_[N];
};
