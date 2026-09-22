#pragma once

#include "../../engine/ecs/Scene.hpp"

class MenuScene : public Scene {
public:
  using Scene::Scene;
  bool init() override;
  void update(float dt) override;
  bool close() override;
};
