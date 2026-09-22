#pragma once

#include "../../engine/core/Scene.hpp"

class MenuScene : public Scene {
public:
  using Scene::Scene;
  bool init() override;
  void update(float dt) override;
  bool close() override;
};
