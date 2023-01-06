#include <Arduino.h>

#include "GoL.h"

#define FRAMES_PER_GENERATION 10
#define FRAMES_PER_RANDOMIZATION (60 * 60)

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

template <int COLS, int ROWS> bool GoL<COLS, ROWS>::init() {
  randomize();
  return true;
}

template <int COLS, int ROWS>
void GoL<COLS, ROWS>::render(int *pixels, const int frame, const int fps) {
  if (frame > 0 && frame % FRAMES_PER_GENERATION == 0) {
    if (frame % FRAMES_PER_RANDOMIZATION == 0) {
      randomize();
    } else {
      nextGeneration();
    }
  }

  memcpy(static_cast<void *>(pixels), cells, sizeof(cells));
}

template <int COLS, int ROWS> void GoL<COLS, ROWS>::randomize() {
  for (int i = 0; i < ROWS * COLS; i++) {
    cells[i] = random() & 1;
  }
}

template <int COLS, int ROWS> void GoL<COLS, ROWS>::nextGeneration() {
  memcpy(static_cast<void *>(next), cells, sizeof(cells));

  bool changed = false;

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      int neighbours = 0;

      for (int i = 0; i < 8; i++) {
        int nrow = (row + NEIGHBOURS[i][0] + ROWS) % ROWS;
        int ncol = (col + NEIGHBOURS[i][1] + COLS) % COLS;

        neighbours += cells[nrow * COLS + ncol];
      }

      int idx = row * COLS + col;

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
    memcpy(static_cast<void *>(cells), next, sizeof(cells));
  } else {
    randomize();
  }
}

GoL<16, 16> gol;
