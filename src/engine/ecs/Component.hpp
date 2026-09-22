#pragma once

// Base tag for all components. The engine only needs this type to store
// components generically; concrete components are defined by the game.
class Component {
public:
  virtual ~Component() = default;
};
