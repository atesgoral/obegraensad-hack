#ifndef ErrorStatusScene_h
#define ErrorStatusScene_h

#include <Scene.h>

class ErrorStatusScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif