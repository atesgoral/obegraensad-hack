#ifndef GoL_h
#define GoL_h

#include <Globals.h>
#include <Scene.h>

class GoL : virtual public Scene {
public:
  virtual bool init();
  virtual void render(int *pixels, const int frame, const int fps);

private:
  int cells[PIXELS];
  int next[sizeof(cells)];

  void randomize();
  void nextGeneration();
};

#endif