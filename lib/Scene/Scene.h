#ifndef Scene_h
#define Scene_h

#include <Globals.h>

class Scene {
public:
  virtual bool init() { return true; }
  virtual void render(char pixels[PIXELS], const int frame) = 0;
  virtual void handle_midi(char status, char data1, char data2) {}
  virtual bool load_wasm(unsigned char wasm[], int length) { return true; };
};

#endif