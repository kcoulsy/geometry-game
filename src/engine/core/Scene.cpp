#include "Scene.hpp"

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

bool Scene::init() { return true; }
void Scene::update(float dt) {}
bool Scene::close() { return true; }
