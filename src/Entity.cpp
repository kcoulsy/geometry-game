#include "Entity.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>

Entity::Entity() {}
Entity::Entity(const std::string& tag, size_t id) {
  m_tag = tag;
  m_id = id;
}

template <typename T, typename... Args>
void Entity::addComponent(Args&&... args) {
  std::get<std::optional<T>>(m_components) = T(std::forward<Args>(args)...);
}

template <typename T>
bool Entity::hasComponent() const {
  return std::get<std::optional<T>>(m_components).has_value();
}

template <typename T>
T& Entity::getComponent() {
  return std::get<std::optional<T>>(m_components);
}

std::string Entity::getTag() { return m_tag; }

bool Entity::getId() { return m_id; }
void Entity::destroy() { m_shouldDieNextFrame = true; }

bool Entity::shouldDieNextFrame() { return m_shouldDieNextFrame; }

EntityManager::EntityManager() {}

void EntityManager::update() {

  for (auto e : m_entitiesToAdd) {
    m_entities.push_back(e);
    m_taggedEntities[e->getTag()].push_back(e);
  }

  m_entitiesToAdd.clear();

  std::vector<int> entitiesToRemove;
  std::map<std::string, std::vector<int>> taggedEntitiesToRemove;

  for (int i = 0; i < m_entities.size(); i++) {
    if (m_entities[i]->shouldDieNextFrame()) {
      entitiesToRemove.push_back(i);
    }
  }

  // go backwards to avoid shifting indexes
  for (int i = static_cast<int>(m_entities.size()) - 1; i >= 0; --i) {
    auto e = m_entities.at(i);

    if (e->shouldDieNextFrame()) {

      const std::string tag = e->getTag();
      m_entities.erase(m_entities.begin() + i);

      auto& teVec = m_taggedEntities[tag];
      for (int j = 0; static_cast<int>(teVec.size()); j++) {
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

void EntityManager::printSize() {
  std::cout << "EM size " << m_entities.size() << std::endl;
}