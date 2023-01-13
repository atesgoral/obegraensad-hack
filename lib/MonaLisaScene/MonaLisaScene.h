#ifndef MonaLisaScene_h
#define MonaLisaScene_h

#include <Scene.h>

class MonaLisaScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif