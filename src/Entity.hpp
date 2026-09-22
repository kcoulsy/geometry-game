#pragma once

#include "Component.hpp"
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Entity {
  friend class EntityManager;

private:
  int m_id = 0;
  bool m_shouldDieNextFrame = false;

  std::string m_tag;
  Components m_components;

  Entity();

public:
  Entity(const std::string& tag, size_t id);
  int getId();
  std::string getTag();

  template <typename T, typename... Args>
  T& addComponent(Args&&... args);

  template <typename T>
  T& addComponent(T component);

  template <typename... Components>
  void addComponents(Components&&... components);

  template <typename T>
  T& getComponent();
  template <typename T>
  bool hasComponent() const;
  template <typename T>
  void removeComponent();

  bool shouldDieNextFrame();

  void destroy();
};

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
private:
  EntityVec m_entities;
  EntityMap m_taggedEntities;
  int m_entityCount = 0;
  EntityVec m_entitiesToAdd;

public:
  EntityManager();
  std::shared_ptr<Entity> createEntity(const std::string& tag);
  EntityVec& getEntities();
  EntityVec& getEntities(const std::string& tag);

  void createPlayer();
  void createBullet(Vec2& startPos, Vec2 towards, float speed);
  void update();
  void printSize();
};

template <typename T, typename... Args>
T& Entity::addComponent(Args&&... args) {
  auto& component = std::get<T>(m_components);
  component = T(std::forward<Args>(args)...);
  component.exists = true;
  return component;
}

template <typename T>
T& Entity::addComponent(T component) {
  auto& existing = std::get<T>(m_components);
  existing = std::move(component);
  existing.exists = true;
  return existing;
}

template <typename... Components>
void Entity::addComponents(Components&&... components) {
  // ugly syntax - this is a fold expression - basically for each of components
  // call add component
  (addComponent(std::forward<Components>(components)), ...);
}

template <typename T>
T& Entity::getComponent() {
  return std::get<T>(m_components);
}

template <typename T>
bool Entity::hasComponent() const {
  return std::get<T>(m_components).exists;
}

template <typename T>
void Entity::removeComponent() {
  return std::get<T>(m_components) = T();
}
