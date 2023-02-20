#include "SceneSwitcher.h"

#include <Globals.h>

#define FADE_FRAME_COUNT ROWS

void SceneSwitcher::render(char pixels[PIXELS], const int frame, float t) {
  if (!m_scene_head) {
    return;
  }

  if (m_current_scene_start == -1) {
    m_current_scene_start = frame;
  }

  int frame_count = frame - m_current_scene_start;
  int elapsed = frame_count / FPS;
  int fade;

  switch (state) {
  case EASE_IN:
    if (frame_count > FADE_FRAME_COUNT) {
      m_current_scene_start = frame;
      state = SHOW;
      fade = -1;
    } else {
      fade = frame_count;
    }
    break;
  case SHOW:
    if (elapsed >= m_current_scene->duration) {
      m_current_scene_start = frame;
      state = EASE_OUT;
      fade = FADE_FRAME_COUNT;
    } else {
      fade = -1;
    }
    break;
  case EASE_OUT:
    if (frame_count > FADE_FRAME_COUNT) {
      m_current_scene =
        m_current_scene->next ? m_current_scene->next : m_scene_head;
      m_current_scene_start = frame;
      m_current_scene->scene->init();

      m_current_scene_start = frame;
      state = EASE_IN;
      fade = 0;
    } else {
      fade = FADE_FRAME_COUNT - frame_count;
    }
    break;
  }

  if (fade == -1) {
    m_current_scene->scene->render(pixels, frame, t);
  } else {
    memset(buffer, 0, sizeof(buffer));

    m_current_scene->scene->render(buffer, frame, t);

    // for (int i = floor(ROWS * fade / FADE_FRAME_COUNT) * COLS; i < PIXELS;
    for (int i = 0; i < PIXELS; i++) {
      // pixels[i] = buffer[i] * fade / FADE_FRAME_COUNT + 0.5;
      pixels[i] = buffer[i];
    }
  }
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