#pragma once

#include "Entity.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Entity;

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

  void update();
  void printSize();
};