#include <Arduino.h>

#include <Globals.h>
#include <Text.h>

#include "OTAStatusScene.h"

void OTAStatusScene::render(char pixels[PIXELS], const int frame, float t) {
  Text::renderText(pixels, "OTA", 0, 4, 0);

  for (int x = 0; x < COLS * m_progress / 100; x++) {
    pixels[AT(x, 15)] = PIXEL_ON;
  }
}

bool OTAStatusScene::set_progress(int progress) {
  if (progress == m_progress) {
    return false;
  }

  m_progress = progress;

  return true;
}
