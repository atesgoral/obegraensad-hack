#ifndef Scene_h
#define Scene_h

class Scene {
public:
  virtual bool init() { return true; }
  virtual void cleanup() {}
  virtual void render(int *pixels, const int frame, const int fps) = 0;
};

#endif