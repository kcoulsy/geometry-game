#include "Render.hpp"

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
  }

  window->display();
}