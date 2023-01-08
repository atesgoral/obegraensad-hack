#ifndef MIDIScene_h
#define MIDIScene_h

#include <Scene.h>

class MIDIScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
  virtual void handle_midi(char status, char data1, char data2);

private:
  char data[COLS] = {};
};

#endif
