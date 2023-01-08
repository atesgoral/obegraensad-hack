#ifndef PWMTestScene_h
#define PWMTestScene_h

#include <Scene.h>

class PWMTestScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif