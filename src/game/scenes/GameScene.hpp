#pragma once

#include "../../engine/ecs/Scene.hpp"
#include "../Entities.hpp"

class GameScene : public Scene {
  EntityFactory m_entities;

public:
  GameScene(sf::RenderWindow* window) : Scene(window), m_entities(&m_entityManager) {}

  EntityFactory& getEntityFactory() { return m_entities; }

  bool init() override;
  void update(float dt) override;
  bool close() override;
};
