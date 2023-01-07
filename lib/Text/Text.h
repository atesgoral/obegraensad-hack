#ifndef Text_h
#define Text_h

#include <Globals.h>

namespace Text {

int renderChar(int pixels[PIXELS], char c, int x, int y);

void renderText(int pixels[PIXELS], const char *text, int x, int y,
                int kerning);
void renderText(int pixels[PIXELS], const char *text, int x, int y);
void renderText4x4(int pixels[PIXELS], const char text[4]);

} // namespace Text

#endif