#ifndef ErrorStatus_h
#define ErrorStatus_h

#include <Scene.h>

class ErrorStatus : virtual public Scene {
public:
  virtual void render(int *pixels, const int frame, const int fps);
};

#endif