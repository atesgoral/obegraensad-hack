#include <Arduino.h>

#include <Bitmap.h>
#include <Globals.h>
#include <Text.h>

#include "PWMTestScene.h"

void PWMTestScene::render(char pixels[PIXELS], const int frame, float t) {
  for (int y = 0; y < ROWS >> 1; y++) {
    int bri = y >> 1;

    for (int x = 0; x < COLS; x++) {
      pixels[AT(x, y)] = bri;
    }
  }

  char buf[3];
  sprintf(buf, "%02X", last_value);

  Text::setColor(3);
  Text::renderText(pixels, buf, 2, 9, 2);
}

void PWMTestScene::handle_midi(char status, char channel, char value) {
  last_value = value;
}