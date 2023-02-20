#include "MIDIScene.h"

void MIDIScene::render(char pixels[PIXELS], const int frame, float t) {
  for (int x = 0; x < COLS; x++) {
    char value = values[x] >> 3;

    for (int y = 0; y <= value; y++) {
      pixels[AT(x, 15 - y)] = PIXEL_ON;
    }
  }
}

void MIDIScene::handle_midi(char status, char channel, char value) {
  values[channel] = value;
}