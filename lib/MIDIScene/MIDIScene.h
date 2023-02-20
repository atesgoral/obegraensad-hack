#ifndef MIDIScene_h
#define MIDIScene_h

#include <Scene.h>

class MIDIScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame, float t);
  virtual void handle_midi(char status, char channel, char value);

private:
  char values[COLS] = {};
};

#endif
