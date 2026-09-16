#pragma once

#include "Vec2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <tuple>

class Component {
public:
  bool exists;
};

class CTransform : public Component {
public:
  Vec2 position = {0, 0};
  float rotation = 0.0f;
  Vec2 scale = {1.0f, 1.0f};
  CTransform() = default;
  CTransform(const Vec2& vp, float r, const Vec2& vs)
      : position(vp), rotation(r), scale(vs) {};
  CTransform(const Vec2& vp) : position(vp) {};
};

class CVelocity : public Component {
public:
  Vec2 velocity = {0.0f, 0.0f};
};

class CRectShape : public Component {
public:
  Vec2 size = {0, 0};
  sf::Color color;
  sf::Color outlineColour;
  float outlineThickness = 0.f;
  CRectShape() = default;
  CRectShape(Vec2 init_size, sf::Color init_color, sf::Color init_outlineColour,
             float init_outlineThickness)
      : size(init_size), color(init_color), outlineColour(init_outlineColour),
        outlineThickness(init_outlineThickness) {}
  sf::RectangleShape shape;
};

class CInput : public Component {
public:
  bool shoot = false;
};

class CShoot : public Component {
public:
  float delayBetweenShots = {0};
  float timeSinceLastShot = {0};
  CShoot() = default;
  // hacky way to allow immediate shooting
  CShoot(float delay) : delayBetweenShots(delay), timeSinceLastShot(delay) {};
};

class CLifetime : public Component {
public:
  float timeUntilDestroy = {0};
  float timeAlive = {0};
  CLifetime() = default;
  CLifetime(float time) : timeUntilDestroy(time) {}
};

typedef std::tuple<CTransform, CVelocity, CRectShape, CInput, CShoot, CLifetime>
    Components;