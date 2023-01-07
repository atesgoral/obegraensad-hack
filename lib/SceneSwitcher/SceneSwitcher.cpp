#include "SceneSwitcher.h"

#include <Globals.h>

void SceneSwitcher::render(int *pixels, const int frame, const int fps) {
  if (!m_scene_head) {
    return;
  }

  if (m_current_scene_start == -1) {
    m_current_scene_start = frame;
  }

  int elapsed = (frame - m_current_scene_start) / FPS;

  if (elapsed >= m_current_scene->duration) {
    m_current_scene =
        m_current_scene->next ? m_current_scene->next : m_scene_head;
    m_current_scene_start = frame;
    m_current_scene->scene->init();
  }

  m_current_scene->scene->render(pixels, frame, fps);
}

void SceneSwitcher::append_scene(Scene *scene, int duration) {
  SceneNode *node = new SceneNode();
  node->scene = scene;
  node->duration = duration;

  if (m_scene_head == NULL) {
    m_scene_head = node;
    m_scene_tail = node;
    m_current_scene = m_scene_head;
    m_current_scene->scene->init();
  } else {
    m_scene_tail->next = node;
    m_scene_tail = node;
  }
}