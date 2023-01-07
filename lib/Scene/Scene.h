#ifndef Scene_h
#define Scene_h

#include <Globals.h>

class Scene {
public:
  virtual bool init() { return true; }
  virtual void cleanup() {}
  virtual void render(int *pixels, const int frame) = 0;
};

#endif