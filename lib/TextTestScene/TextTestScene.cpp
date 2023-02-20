#include <Arduino.h>

#include <Globals.h>
#include <Text2.h>

#include "TextTestScene.h"

void TextTestScene::render(char pixels[PIXELS], const int frame, float t) {
  Text2::renderText(pixels, "ABCD", 0, 0, 0);
  Text2::renderText(pixels, "abcd", 0, 8, 0);
}
