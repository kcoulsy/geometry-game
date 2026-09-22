#include "Scene.hpp"
#include "Systems.hpp"

SceneManger::~SceneManger() {
  delete m_current;
  delete m_next;
}

bool SceneManger::goToScene(Scene* scene) {
  if (!scene)
    return false;

  // queue it; the swap happens in resolve() once no scene is mid-update
  delete m_next;
  m_next = scene;

  return true;
}

void SceneManger::resolve() {
  if (!m_next)
    return;

  Scene* next = m_next;
  m_next = nullptr;

  next->preInit(this);
  if (!next->init()) {
    delete next;
    return;
  }

  if (m_current) {
    m_current->close();
    delete m_current;
  }

  m_current = next;
}

EntityManager* Scene::getEntityManager() { return &m_entityManager; }
EntityFactory* Scene::getEntityFactory() { return m_entities; }

bool Scene::init() { return true; }
void Scene::update(float dt) {}
bool Scene::close() { return true; }

bool MenuScene::init() {
  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    return false;
  }

  getEntityManager()->createEntity("ui")->addComponents(CUIText("Press Space to start"));
  getEntityManager()->printSize();

  return true;
}

void MenuScene::update(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    m_sceneManager->goToScene(new GameScene(getWindow()));
  }
  getEntityManager()->update();
  getWindow()->clear(sf::Color::Black);
  sRenderUI(this);
  getWindow()->display();
}

bool MenuScene::close() { return true; }

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

bool GameScene::close() { return true; }