#ifndef PWMTestScene_h
#define PWMTestScene_h

#include <Scene.h>

class PWMTestScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame, float t);
  virtual void handle_midi(char status, char channel, char value);

private:
  int last_value = 0;
};

#endif