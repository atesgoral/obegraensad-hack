#ifndef Clock_h
#define Clock_h

#include <Scene.h>

class Clock : virtual public Scene {
public:
  virtual bool init();
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif