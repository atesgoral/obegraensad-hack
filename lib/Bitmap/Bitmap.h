#ifndef Bitmap_h
#define Bitmap_h

#include <Globals.h>

namespace Bitmap {

void renderBitmap(char pixels[PIXELS], const char *bitmap, char color);
void renderBitmap(char pixels[PIXELS], const char *bitmap);

} // namespace Bitmap

#endif