#ifndef GoL_h
#define GoL_h

#include <Scene.h>

class GoL : virtual public Scene {
public:
  virtual bool init();
  virtual void render(int pixels[PIXELS], const int frame);

private:
  int cells[PIXELS];
  int next[sizeof(cells)];

  void randomize();
  void nextGeneration();
};

#endif