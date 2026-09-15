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
  // to change
  std::string m_tag;
  std::tuple<Component> m_components;

  Entity();

public:
  Entity(const std::string& tag, size_t id);
  bool getId();
  std::string getTag();
  template <typename T, typename... Args>
  void addComponent(Args&&... args);
  template <typename T>
  T& getComponent();
  template <typename T>
  bool hasComponent() const;

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
  void update();
  void printSize();
};