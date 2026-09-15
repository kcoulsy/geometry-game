#include "Vec2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <optional>
#include <tuple>
#include <utility>

class Component {
public:
  bool exists;
};

class CTransform : public Component {
public:
  Vec2 position = {0, 0};
  float rotation = 0.0f;
  Vec2 scale = {1.0f, 1.0f};
};

class CVelocity {
public:
  Vec2 velocity = {0.0f, 0.0f};
};

class CRectShape : public Component {
public:
  Vec2 size = {0, 0};
  sf::Color color;
  sf::Color outlineColour;
  float outlineThickness;
  CRectShape();
  CRectShape(Vec2 init_size, sf::Color init_color, sf::Color init_outlineColour,
             float init_outlineThickness)
      : size(init_size), color(init_color), outlineColour(init_outlineColour),
        outlineThickness(init_outlineThickness) {}
  sf::RectangleShape shape;
};

typedef std::tuple<std::optional<CTransform>, std::optional<CVelocity>,
                   std::optional<CRectShape>>
    Components;