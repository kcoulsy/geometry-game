#include "Render.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

void sRender(Game* gameCtx) {
  auto em = gameCtx->getEntityManager();
  auto window = gameCtx->getWindow();
  window->clear(sf::Color::Cyan);

  auto& entities = em->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CRectShape>() && e->hasComponent<CTransform>()) {
      auto& cs = e->getComponent<CRectShape>();
      auto& ct = e->getComponent<CTransform>();
      cs.shape.setOrigin(sf::Vector2f(cs.size.x / 2, cs.size.y / 2));
      cs.shape.setPosition(sf::Vector2f(ct.position.x, ct.position.y));
      cs.shape.setSize(sf::Vector2f(cs.size.x, cs.size.y));
      cs.shape.setFillColor(cs.color);
      cs.shape.setOutlineColor(cs.outlineColour);
      cs.shape.setOutlineThickness(cs.outlineThickness);
      window->draw(cs.shape);
    }
    if (e->hasComponent<CPolyShape>() && e->hasComponent<CTransform>()) {
      auto& cs = e->getComponent<CPolyShape>();
      auto& ct = e->getComponent<CTransform>();
      // cs.shape.setOrigin(sf::Vector2f(cs.size.x / 2, cs.size.y / 2));
      cs.shape.setPosition(sf::Vector2f(ct.position.x, ct.position.y));
      cs.shape.setPointCount(cs.sides);
      cs.shape.setRadius(cs.radius);
      cs.shape.setFillColor(cs.color);
      cs.shape.setOutlineColor(cs.outlineColour);
      cs.shape.setOutlineThickness(cs.outlineThickness);
      window->draw(cs.shape);
    }
    if (e->hasComponent<CBoundingBox>()) {
      auto& cbb = e->getComponent<CBoundingBox>();
      if (cbb.debug) {
        auto& ct = e->getComponent<CTransform>();
        cbb.debugShape.setOrigin(sf::Vector2f(cbb.width / 2, cbb.height / 2));
        cbb.debugShape.setSize(sf::Vector2f(cbb.width, cbb.height));
        cbb.debugShape.setPosition(sf::Vector2f(ct.position.x + cbb.offset.x,
                                                ct.position.y + cbb.offset.y));
        cbb.debugShape.setFillColor(sf::Color::Transparent);
        cbb.debugShape.setOutlineColor(sf::Color::Red);
        cbb.debugShape.setOutlineThickness(2.f);
        window->draw(cbb.debugShape);
      }
    }
  }

  window->display();
}