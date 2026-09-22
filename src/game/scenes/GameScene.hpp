#pragma once

#include "../../engine/ecs/Scene.hpp"

class GameScene : public Scene {
public:
  using Scene::Scene;
  bool init() override;
  void update(float dt) override;
  bool close() override;
};
