#include "Bitmap.h"

#include <Globals.h>

void Bitmap::renderBitmap(int *pixels, const int *bitmap) {
  for (int i = 0; i < COLS; i++) {
    for (int j = 0; j < ROWS; j++) {
      pixels[AT(i, j)] = bitmap[AT(i, j)];
    }
  }
}