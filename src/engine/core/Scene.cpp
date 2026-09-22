#include "Scene.hpp"

EntityManager* Scene::getEntityManager() { return &m_entityManager; }

bool Scene::init() { return true; }
void Scene::update(float dt) {}
bool Scene::close() { return true; }
