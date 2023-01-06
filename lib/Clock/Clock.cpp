#include <Arduino.h>
#include <Text.h>

#include "Clock.h"

const char NTP_SERVER[] = "pool.ntp.org";

void clockDigits(char *buf, int component) {
  snprintf(buf, sizeof(buf), "%02d", component);

  for (int i = 0; i < 2; i++) {
    if (buf[i] == '0') {
      buf[i] = 'O';
    }
  }
}

bool Clock::init() {
  const long gmt_offset_sec = -5 * 60 * 60;
  const int dst_offset_sec = 0;

  configTime(gmt_offset_sec, dst_offset_sec, NTP_SERVER);

  return true;
}

void Clock::render(int *pixels, const int frame, const int fps) {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    return;
  }

  char buf[2 + 1];

  clockDigits(buf, timeinfo.tm_hour);
  Text::renderText(pixels, buf, 2, 0, 2);

  clockDigits(buf, timeinfo.tm_min);
  Text::renderText(pixels, buf, 2, 9, 2);

  if (timeinfo.tm_sec & 1) {
    pixels[7 * 16 + 7] = 1;
    pixels[8 * 16 + 8] = 1;
  } else {
    pixels[7 * 16 + 8] = 1;
    pixels[8 * 16 + 7] = 1;
  }
}
