#ifndef GoL_h
#define GoL_h

#include <Scene.h>

template <int COLS, int ROWS> class GoL : virtual public Scene {
public:
  virtual bool init();
  virtual void render(int *pixels, const int frame, const int fps);

private:
  int cells[ROWS * COLS];
  int next[sizeof(cells)];

  void randomize();
  void nextGeneration();
};

#endif