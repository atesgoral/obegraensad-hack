#ifndef TEXT2_H
#define TEXT2_H

#include <Globals.h>

namespace Text2 {

int renderChar(char pixels[PIXELS], char c, int x, int y);

void renderText(char pixels[PIXELS], const char *text, int x, int y,
                int kerning);
void renderText(char pixels[PIXELS], const char *text, int x, int y);

} // namespace Text2

#endif