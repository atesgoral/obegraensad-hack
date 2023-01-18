#ifndef WASM_TEST_SCENE_H
#define WASM_TEST_SCENE_H

#include <m3_env.h>
// #include <wasm3.h>

#include <Scene.h>

class WasmTestScene : virtual public Scene {
public:
  virtual bool init();
  virtual void render(char pixels[PIXELS], const int frame);

private:
  IM3Environment m3_env;
  IM3Runtime m3_runtime;
  IM3Module m3_module;
  IM3Function m3_render;
  const char *m3_pixels;
};

#endif