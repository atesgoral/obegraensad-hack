#include <Arduino.h>

#include <Globals.h>
#include <Text.h>

#include "WiFiStatusScene.h"

void WiFiStatusScene::render(char pixels[PIXELS], const int frame, float t) {
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

  pixels[y * ROWS + x] = PIXEL_ON;
}
