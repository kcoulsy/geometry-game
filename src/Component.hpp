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

typedef std::tuple<CTransform, CVelocity, CRectShape> Components;