#include "Bitmap.h"

#include <Globals.h>

void Bitmap::renderBitmap(char pixels[PIXELS], const char *bitmap, char color) {
  for (int i = 0; i < COLS; i++) {
    for (int j = 0; j < ROWS; j++) {
      char pixel = bitmap[AT(i, j)];
      pixels[AT(i, j)] = pixel ? color == -1 ? pixel : color : PIXEL_OFF;
      pixels[AT(i, j)] = pixel;
    }
  }
}

void Bitmap::renderBitmap(char pixels[PIXELS], const char *bitmap) {
  renderBitmap(pixels, bitmap, -1);
}