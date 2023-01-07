#ifndef Text_h
#define Text_h

#include <Globals.h>

namespace Text {

int renderChar(char pixels[PIXELS], char c, int x, int y);

void renderText(char pixels[PIXELS], const char *text, int x, int y,
                int kerning);
void renderText(char pixels[PIXELS], const char *text, int x, int y);
void renderText4x4(char pixels[PIXELS], const char text[4]);

} // namespace Text

#endif