#include <Arduino.h>

#include "GoLScene.h"

#define FRAMES_PER_GENERATION (FPS / 6)
#define FRAMES_PER_RANDOMIZATION (60 * FPS)

// Neighbour offsets
// clang-format off
const int NEIGHBOURS[][2] = {
  {0, -1},
  {1, -1},
  {1, 0},
  {1, 1},
  {0, 1},
  {-1, 1},
  {-1, 0},
  {-1, -1}
};
// clang-format on

bool GoLScene::init() {
  randomize();
  return true;
}

void GoLScene::render(char pixels[PIXELS], const int frame, float t) {
  if (frame > 0 && frame % FRAMES_PER_GENERATION == 0) {
    if (frame % FRAMES_PER_RANDOMIZATION == 0) {
      randomize();
    } else {
      nextGeneration();
    }
  }

  for (int i = 0; i < PIXELS; i++) {
    pixels[i] = cells[i] ? PIXEL_ON : PIXEL_OFF;
  }
}

void GoLScene::randomize() {
  for (int i = 0; i < PIXELS; i++) {
    cells[i] = random() & 1;
  }
}

void GoLScene::nextGeneration() {
  memcpy(static_cast<void *>(next), cells, sizeof(cells));

  bool changed = false;

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      int neighbours = 0;

      for (int i = 0; i < 8; i++) {
        int nrow = (row + NEIGHBOURS[i][0] + ROWS) % ROWS;
        int ncol = (col + NEIGHBOURS[i][1] + COLS) % COLS;

        neighbours += cells[AT(ncol, nrow)];
      }

      int idx = AT(col, row);

      if (cells[idx] == 1) {
        if (neighbours < 2 || neighbours > 3) {
          next[idx] = 0;
          changed = true;
        }
      } else {
        if (neighbours == 3) {
          next[idx] = 1;
          changed = true;
        }
      }
    }
  }

  if (changed) {
    for (int i = 0; i < PIXELS; i++) {
      cells[i] = next[i];
    }
  } else {
    randomize();
  }
}
