#ifndef Clock_h
#define Clock_h

#include <Scene.h>

class Clock : virtual public Scene {
public:
  virtual bool init();
  virtual void render(int *pixels, const int frame);
};

#endif