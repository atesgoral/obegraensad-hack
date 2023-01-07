#ifndef SceneSwitcher_h
#define SceneSwitcher_h

#include <Arduino.h>
#include <Scene.h>

typedef struct SceneNode {
  Scene *scene;
  int duration;
  struct SceneNode *next;
} SceneNode;

class SceneSwitcher : virtual public Scene {
public:
  virtual void render(int *pixels, const int frame, const int fps);
  void append_scene(Scene *scene, int duration);

private:
  SceneNode *m_scene_head = NULL;
  SceneNode *m_scene_tail = NULL;
  SceneNode *m_current_scene = NULL;
  int m_current_scene_start = -1;
};

#endif