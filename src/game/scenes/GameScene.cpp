#include "GameScene.hpp"
#include "../systems/Systems.hpp"

bool GameScene::init() {

  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    return false;
  }

  m_entities.createPlayer(static_cast<float>(getWindow()->getSize().x) / 2,
                          static_cast<float>(getWindow()->getSize().y) / 2);
  m_entities.createEnemyManger();
  m_entities.createScoreUI();
  m_entities.createDebugUI();

  return true;
}

void GameScene::update(float dt) {
  m_entityManager.update();

  sLifetime(this, dt);
  sInput(this);
  sPlayerShoot(this, m_entities, dt);
  sBulletCollision(this);
  sPhysics(this, dt);
  sMovement(this, dt);
  sEnemySpawner(this, m_entities, dt);
  sDebugUI(this, dt);
  sRender(this);
  sRenderUI(this);

  getWindow()->display();
}

bool GameScene::close() { return true; }