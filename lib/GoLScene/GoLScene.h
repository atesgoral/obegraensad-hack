#ifndef GoLScene_h
#define GoLScene_h

#include <Scene.h>

class GoLScene : virtual public Scene {
public:
  virtual bool init();
  virtual void render(char pixels[PIXELS], const int frame);

private:
  char cells[PIXELS];
  char next[sizeof(cells)];

  void randomize();
  void nextGeneration();
};

#endif