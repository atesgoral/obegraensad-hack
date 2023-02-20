#include <Arduino.h>
#include <Text.h>

#include "ClockScene.h"

const char NTP_SERVER[] = "pool.ntp.org";

void clockDigits(char *buf, int component) {
  int first_digit = component / 10;
  int second_digit = component % 10;

  buf[0] = first_digit ? first_digit + '0' : 'O';
  buf[1] = second_digit ? second_digit + '0' : 'O';
  buf[2] = '\0';
}

bool ClockScene::init() {
  const long gmt_offset_sec = -5 * 60 * 60;
  const int dst_offset_sec = 0;

  configTime(gmt_offset_sec, dst_offset_sec, NTP_SERVER);

  return true;
}

void ClockScene::render(char pixels[PIXELS], const int frame, float t) {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    return;
  }

  char hhmm[4 + 1];

  clockDigits(hhmm, timeinfo.tm_hour);
  clockDigits(hhmm + 2, timeinfo.tm_min);
  Text::renderText4x4(pixels, hhmm);

  if (timeinfo.tm_sec & 1) {
    pixels[7 * 16 + 7] = PIXEL_ON;
    pixels[8 * 16 + 8] = PIXEL_ON;
  } else {
    pixels[7 * 16 + 8] = PIXEL_ON;
    pixels[8 * 16 + 7] = PIXEL_ON;
  }
}
