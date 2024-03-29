#include <Arduino.h>

#include "WasmScene.h"

#include "scene.wasm.h"

#define WASM_STACK_SLOTS 1024
#define WASM_MEMORY_LIMIT 4096

bool WasmScene::init() {
  m3_env = m3_NewEnvironment();

  if (!m3_env) {
    Serial.println("Failed to create Wasm3 environment");
    return false;
  }

  m3_runtime = m3_NewRuntime(m3_env, WASM_STACK_SLOTS, NULL);

  if (!m3_runtime) {
    Serial.println("Failed to create Wasm3 runtime");
    return false;
  }

  m3_runtime->memoryLimit = WASM_MEMORY_LIMIT;

  return this->load_wasm(scene_wasm, sizeof(scene_wasm));
  // return true;
}

void WasmScene::render(char pixels[PIXELS], const int frame, float t) {
  if (!m3_render) {
    return;
  }

  M3Result result = m3_CallV(m3_render, frame, t);

  if (result) {
    Serial.print("Failed to call Wasm function: ");
    Serial.println(result);
    return;
  }

  memcpy(pixels, m3_pixels, PIXELS);
}

bool WasmScene::load_wasm(unsigned char wasm[], int length) {
  M3Result result = m3_ParseModule(m3_env, &m3_module, wasm, length);

  if (result) {
    Serial.print("Failed to parse Wasm module: ");
    Serial.println(result);
    return false;
  }

  result = m3_LoadModule(m3_runtime, m3_module);

  if (result) {
    Serial.print("Failed to load Wasm module: ");
    Serial.println(result);
    return false;
  }

  result = m3_FindFunction(&m3_render, m3_runtime, "render");

  if (result) {
    Serial.print("Failed to find Wasm function: ");
    Serial.println(result);
    return false;
  }

  size_t size;
  m3_pixels = (const char *)(m3_GetMemory(m3_runtime, &size, 0));

  if (size < PIXELS) {
    Serial.print("Wasm memory too small: ");
    Serial.println(size);
    return false;
  }

  return true;
}
