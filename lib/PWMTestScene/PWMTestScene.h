#ifndef PWMTestScene_h
#define PWMTestScene_h

#include <Scene.h>

class PWMTestScene : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
  virtual void handle_midi(char status, char channel, char value);

private:
  int16_t dc_max = 0x1e;
  int dcs[4] = {0, 0x05, 0x1a, 0x7f};
  int last_value = 0;
};

#endif