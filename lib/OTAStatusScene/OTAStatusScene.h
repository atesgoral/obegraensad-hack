#ifndef OTAStatusScene_h
#define OTAStatusScene_h

#include <Scene.h>

class OTAStatusScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame, float t);
  bool set_progress(int progress);

private:
  int m_progress = -1;
};

#endif