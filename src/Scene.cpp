#include "Scene.hpp"
#include "Systems.hpp"

EntityManager* Scene::getEntityManager() { return &m_entityManager; }
EntityFactory* Scene::getEntityFactory() { return m_entities; }

bool Scene::init() {}
void Scene::update(float dt) {}
bool Scene::close() {}

bool GameScene::init() {

  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    return false;
  }

  m_entities->createPlayer(static_cast<float>(getWindow()->getSize().x) / 2,
                           static_cast<float>(getWindow()->getSize().y) / 2);
  m_entities->createEnemyManger();
  m_entities->createScoreUI();
  m_entities->createDebugUI();

  return true;
}

void GameScene::update(float dt) {
  m_entityManager.update();

  sLifetime(this, dt);
  sInput(this);
  sPlayerShoot(this, dt);
  sBulletCollision(this);
  sPhysics(this, dt);
  sMovement(this, dt);
  sEnemySpawner(this, dt);
  sDebugUI(this, dt);
  sRender(this);
  sRenderUI(this);

  getWindow()->display();
}

bool GameScene::close() {}