#include "MIDIScene.h"

void MIDIScene::render(char pixels[PIXELS], const int frame) {
  for (int x = 0; x < COLS; x++) {
    char value = values[x] >> 3;

    for (int y = 0; y <= value; y++) {
      pixels[AT(x, 15 - y)] = 1;
    }
  }
}

void MIDIScene::handle_midi(char status, char channel, char value) {
  values[channel] = value;
}