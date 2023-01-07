namespace Text {

int renderChar(int *pixels, char c, int x, int y);

void renderText(int *pixels, const char *text, int x, int y, int kerning);
void renderText(int *pixels, const char *text, int x, int y);
void renderText4x4(int *pixels, const char text[4]);

}