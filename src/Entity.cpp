#include "Entity.hpp"
#include <optional>

Entity::Entity() {}

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