#ifndef METABALLS_SCENE_H
#define METABALLS_SCENE_H

#include <Scene.h>

class MetaballsScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
};

#endif
