#ifndef WiFiStatus_h
#define WiFiStatus_h

#include <Scene.h>

class WiFiStatus : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif