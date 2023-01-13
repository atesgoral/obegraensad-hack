#ifndef TextTestScene_h
#define TextTestScene_h

#include <Scene.h>

class TextTestScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif