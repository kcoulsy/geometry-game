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
};

class CRectShape : public Component {
public:
  Vec2 size = {0, 0};
  sf::Color color;
  sf::Color outlineColour;
  float outlineThickness;
  CRectShape();
  CRectShape(Vec2 size, sf::Color color, sf::Color outlineColour,
             float outlineThickness);
  sf::RectangleShape shape;
};

typedef std::tuple<std::optional<CTransform>, std::optional<CRectShape>>
    Components;