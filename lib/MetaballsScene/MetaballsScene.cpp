#include <Arduino.h>

#include <Globals.h>

#include "MetaballsScene.h"

float clamp(float x, float min, float max) {
  return x < min ? min : x > max ? max : x;
}

float smoothstep(float edge0, float edge1, float x) {
  float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
  return t * t * (3 - 2 * t);
}

void MetaballsScene::render(char pixels[PIXELS], const int frame, float t) {
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      float d = 0;

      d +=
        3 /
        hypot(
          7.5 + sin(t * 1.1 / FPS) * 7.5 - x, 7.5 + cos(t * 1.3 / FPS) * 7.5 - y
        );
      d +=
        2 /
        hypot(
          7.5 + sin(t * 1.5 / FPS) * 7.5 - x, 7.5 + cos(t * 1.7 / FPS) * 7.5 - y
        );
      d +=
        1 /
        hypot(
          7.5 + sin(t * 1.9 / FPS) * 7.5 - x, 7.5 + cos(t * 2.1 / FPS) * 7.5 - y
        );

      pixels[y * COLS + x] = round(smoothstep(0.75, 1.0, d) * PIXEL_ON);
    }
  }
}
