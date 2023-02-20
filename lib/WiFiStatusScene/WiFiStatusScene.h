#ifndef WiFiStatusScene_h
#define WiFiStatusScene_h

#include <Scene.h>

class WiFiStatusScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame, float t);
};

#endif