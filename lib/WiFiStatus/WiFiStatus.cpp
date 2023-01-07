#include <Arduino.h>

#include <Globals.h>
#include <Text.h>

#include "WiFiStatus.h"

void WiFiStatus::render(int *pixels, const int frame, const int fps) {
  Text::renderText4x4(pixels, "WiFi");

  int x = 7;
  int y = 7;

  switch (frame >> 3 & 3) {
  case 1:
    x++;
    break;
  case 2:
    x++;
    y++;
    break;
  case 3:
    y++;
    break;
  }

  pixels[y * ROWS + x] = 1;
}
