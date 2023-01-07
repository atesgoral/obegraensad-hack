#ifndef ErrorStatus_h
#define ErrorStatus_h

#include <Scene.h>

class ErrorStatus : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif