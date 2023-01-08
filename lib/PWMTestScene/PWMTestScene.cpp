#include <Arduino.h>

#include <Bitmap.h>
#include <Globals.h>

#include "PWMTestScene.h"

int DCS[4] = {0, 1, 7, 30};

void PWMTestScene::render(char pixels[PIXELS], const int frame) {
  int dc = frame % 30;

  for (int y = 0; y < COLS; y++) {
    int bri = y >> 2;
    char on = DCS[bri] > dc;

    for (int x = 0; x < COLS; x++) {
      pixels[AT(x, y)] = on;
    }
  }
}