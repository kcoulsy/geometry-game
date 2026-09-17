#pragma once

#include "Vec2.hpp"
#include <SFML/Graphics/CircleShape.hpp>
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

class CPolyShape : public Component {
public:
  float radius = 0.f;
  sf::Color color;
  sf::Color outlineColour;
  float outlineThickness = 0.f;
  int sides = 3;
  CPolyShape() = default;
  CPolyShape(float init_radius, sf::Color init_color,
             sf::Color init_outlineColour, float init_outlineThickness,
             int init_sides)
      : radius(init_radius), color(init_color),
        outlineColour(init_outlineColour),
        outlineThickness(init_outlineThickness), sides(init_sides) {}
  sf::CircleShape shape;
};

class CInput : public Component {
public:
  bool shoot = false;
};

class CShoot : public Component {
public:
  float delayBetweenShots = {0};
  float timeSinceLastShot = {0};
  float bulletSpeed = {10.f};
  CShoot() = default;
  // hacky way to allow immediate shooting
  CShoot(float delay, float speed)
      : delayBetweenShots(delay), timeSinceLastShot(delay),
        bulletSpeed(speed) {};
};

class CLifetime : public Component {
public:
  float timeUntilDestroy = {0};
  float timeAlive = {0};
  CLifetime() = default;
  CLifetime(float time) : timeUntilDestroy(time) {}
};

class CEnemyManager : public Component {
public:
  int currentEnemyCount = 0;
  int maxEnemies = 5;
  float spawnInterval = {0};
  float timeSinceLastSpawn = {0};
  CEnemyManager() = default;
  CEnemyManager(int max, float interval)
      : maxEnemies(max), spawnInterval(interval), timeSinceLastSpawn(interval) {
  }
};

typedef std::tuple<CTransform, CVelocity, CRectShape, CInput, CShoot, CLifetime,
                   CPolyShape, CEnemyManager>
    Components;