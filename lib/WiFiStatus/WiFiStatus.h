#ifndef WiFiStatus_h
#define WiFiStatus_h

#include <Scene.h>

class WiFiStatus : virtual public Scene {
public:
  virtual void render(int *pixels, const int frame);
};

#endif