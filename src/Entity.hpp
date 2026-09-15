#pragma once

#include "Component.hpp"
#include <string>

class Entity {
public:
  int m_id = 0;
  bool m_shouldDieNextFrame = false;
  // to change
  std::string m_tag;
  std::tuple<Component> m_components;

private:
  Entity();

  template <typename T, typename... Args>
  void addComponent(Args&&... args);
  template <typename T>
  T& getComponent();
  template <typename T>
  bool hasComponent() const;

  void destroy();
};