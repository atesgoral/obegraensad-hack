#include <Arduino.h>

#include <Globals.h>
#include <Text.h>

#include "OTAStatus.h"

void OTAStatus::render(int pixels[PIXELS], const int frame) {
  Text::renderText(pixels, "OTA", 0, 4, 0);

  for (int x = 0; x < COLS * m_progress / 100; x++) {
    pixels[AT(x, 15)] = 1;
  }
}

bool OTAStatus::set_progress(int progress) {
  if (progress == m_progress) {
    return false;
  }

  m_progress = progress;

  return true;
}
