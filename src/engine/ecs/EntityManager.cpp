#include "EntityManager.hpp"
#include <iostream>
#include <memory>

EntityManager::EntityManager() {}

void EntityManager::update() {

  for (auto e : m_entitiesToAdd) {
    m_entities.push_back(e);
    m_taggedEntities[e->getTag()].push_back(e);
  }

  m_entitiesToAdd.clear();

  // go backwards to avoid shifting indexes
  for (int i = static_cast<int>(m_entities.size()) - 1; i >= 0; --i) {
    auto e = m_entities.at(i);

    if (e->shouldDieNextFrame()) {

      const std::string tag = e->getTag();
      m_entities.erase(m_entities.begin() + i);

      auto& teVec = m_taggedEntities[tag];
      for (int j = 0; j < static_cast<int>(teVec.size()); j++) {
        if (teVec.at(j)->getId() == e->getId()) {
          teVec.erase(teVec.begin() + j);
          break;
        }
      }
    }
  }
}

std::shared_ptr<Entity> EntityManager::createEntity(const std::string& tag) {
  auto e = std::make_shared<Entity>(tag, m_entityCount++);
  m_entitiesToAdd.push_back(e);

  return e;
}

EntityVec& EntityManager::getEntities() { return m_entities; }
EntityVec& EntityManager::getEntities(const std::string& tag) { return m_taggedEntities[tag]; }
EntityVec& getEntities(const std::string& tag);
void EntityManager::printSize() { std::cout << "EM size " << m_entities.size() << std::endl; }