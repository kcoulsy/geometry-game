#include "Entity.hpp"
#include <cstddef>

Entity::Entity() {}
Entity::Entity(const std::string& tag, size_t id) {
  m_tag = tag;
  m_id = id;
}

std::string Entity::getTag() { return m_tag; }

int Entity::getId() { return m_id; }
void Entity::destroy() { m_shouldDieNextFrame = true; }

bool Entity::shouldDieNextFrame() { return m_shouldDieNextFrame; }