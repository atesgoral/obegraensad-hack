#ifndef ClockScene_h
#define ClockScene_h

#include <Scene.h>

class ClockScene : virtual public Scene {
public:
  virtual bool init();
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif