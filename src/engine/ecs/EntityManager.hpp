#pragma once

#include "Entity.hpp"
#include <memory>
#include <string>

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

  void update();
  void printSize();
};