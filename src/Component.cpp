

#include "Component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <tuple>

CRectShape::CRectShape(Vec2 init_size, sf::Color init_color,
                       sf::Color init_outlineColour,
                       float init_outlineThickness)
    : size(init_size), color(init_color), outlineColour(init_outlineColour),
      outlineThickness(init_outlineThickness) {}