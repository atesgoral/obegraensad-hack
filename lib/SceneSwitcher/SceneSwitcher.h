#ifndef SceneSwitcher_h
#define SceneSwitcher_h

#include <Arduino.h>
#include <Scene.h>

#define EASE_IN 0
#define SHOW 1
#define EASE_OUT 2

typedef struct SceneNode {
  Scene *scene;
  int duration;
  struct SceneNode *next;
} SceneNode;

class SceneSwitcher : virtual public Scene {
public:
  virtual void render(char pixels[PIXELS], const int frame);
  void append_scene(Scene *scene, int duration);

private:
  SceneNode *m_scene_head = NULL;
  SceneNode *m_scene_tail = NULL;
  SceneNode *m_current_scene = NULL;
  int m_current_scene_start = -1;
  int state = EASE_IN;
  char buffer[PIXELS];
};

#endif