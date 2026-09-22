#pragma once

#include "Entity.hpp"
#include "Vec2.hpp"

class EntityFactory {
public:
  void createPlayer(float xPos, float yPos);
  void createBullet(Vec2& startPos, Vec2 towards, float speed);
  void createEnemy(float xPos, float yPos);
  void createEnemyManger();
  void createScoreUI();
  void createDebugUI();
  EntityFactory(EntityManager* em) : m_entityManager(em) {}

private:
  EntityManager* m_entityManager;
};