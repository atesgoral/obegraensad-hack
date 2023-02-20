#ifndef MarioScene_h
#define MarioScene_h

#include <Scene.h>

class MarioScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame, float t);
};

#endif