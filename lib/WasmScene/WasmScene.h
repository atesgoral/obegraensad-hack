#ifndef WASM_SCENE_H
#define WASM_SCENE_H

#include <m3_env.h>
// #include <wasm3.h>

#include <Scene.h>

class WasmScene : virtual public Scene {
public:
  virtual bool init();
  virtual void render(char pixels[PIXELS], const int frame);
  bool load_wasm(unsigned char wasm[], int length);

private:
  IM3Environment m3_env;
  IM3Runtime m3_runtime;
  IM3Module m3_module;
  IM3Function m3_render;
  const char *m3_pixels;
};

#endif