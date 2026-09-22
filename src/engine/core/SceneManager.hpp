#pragma once

#include "Scene.hpp"

class SceneManager {
  Scene* m_current = nullptr;
  Scene* m_next = nullptr;

public:
  SceneManager() = default;
  ~SceneManager();
  bool goToScene(Scene* scene);
  void resolve();
  Scene* getCurrent() { return m_current; }
};
