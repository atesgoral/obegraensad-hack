#ifndef Scene_h
#define Scene_h

#include <Globals.h>

class Scene {
public:
  virtual bool init() { return true; }
  virtual void cleanup() {}
  virtual void render(char pixels[PIXELS], const int frame) = 0;
};

#endif