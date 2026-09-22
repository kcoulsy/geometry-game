#pragma once

#include "Component.hpp"
#include <concepts>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
concept IsComponent = std::derived_from<T, Component>;

class Entity {
  friend class EntityManager;

private:
  int m_id = 0;
  bool m_shouldDieNextFrame = false;

  std::string m_tag;
  std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

  Entity();

public:
  Entity(const std::string& tag, size_t id);
  int getId();
  std::string getTag();

  template <IsComponent T>
  T& addComponent(T component);

  template <IsComponent... Ts>
  void addComponents(Ts&&... components);

  template <IsComponent T>
  T& getComponent();

  template <IsComponent T>
  bool hasComponent() const;

  template <IsComponent... Ts>
  bool hasComponents() const;

  template <IsComponent T>
  void removeComponent();

  bool shouldDieNextFrame();

  void destroy();
};

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

template <IsComponent T>
T& Entity::addComponent(T component) {
  auto owned = std::make_unique<T>(std::move(component));
  T& ref = *owned;
  m_components[std::type_index(typeid(T))] = std::move(owned);
  return ref;
}

template <IsComponent... Ts>
void Entity::addComponents(Ts&&... components) {
  // fold expression: call addComponent for each argument
  (addComponent(std::forward<Ts>(components)), ...);
}

template <IsComponent T>
T& Entity::getComponent() {
  return static_cast<T&>(*m_components.at(std::type_index(typeid(T))));
}

template <IsComponent T>
bool Entity::hasComponent() const {
  return m_components.contains(std::type_index(typeid(T)));
}

template <IsComponent... Ts>
bool Entity::hasComponents() const {
  return (m_components.contains(std::type_index(typeid(Ts))) && ...);
}

template <IsComponent T>
void Entity::removeComponent() {
  m_components.erase(std::type_index(typeid(T)));
}
