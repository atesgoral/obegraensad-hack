#ifndef OTAStatus_h
#define OTAStatus_h

#include <Scene.h>

class OTAStatus : virtual public Scene {
public:
  virtual void render(int *pixels, const int frame);
  bool set_progress(int progress);

private:
  int m_progress = -1;
};

#endif