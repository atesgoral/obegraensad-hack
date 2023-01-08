#include <Arduino.h>

#include <Bitmap.h>
#include <Globals.h>
#include <Text.h>

#include "PWMTestScene.h"

void PWMTestScene::render(char pixels[PIXELS], const int frame) {
  int dc = frame % dc_max;
  int scaled_dcs[4];

  for (int i = 0; i < 4; i++) {
    scaled_dcs[i] = dcs[i] * dc_max / 0x7f;
  }

  for (int y = 0; y < ROWS >> 1; y++) {
    int bri = y >> 1;
    char on = scaled_dcs[bri] > dc;

    for (int x = 0; x < COLS; x++) {
      pixels[AT(x, y)] = on;
    }
  }

  char buf[3];
  sprintf(buf, "%02x", last_value);
  Text::renderText(pixels, buf, 2, 9, 2);
}

void PWMTestScene::handle_midi(char status, char channel, char value) {
  if (channel < 4) {
    dcs[channel] = value;
  } else if (channel == 4) {
    dc_max = value ? value : 1;
  }

  last_value = value;
}