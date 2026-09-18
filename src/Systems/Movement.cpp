#include "Movement.hpp"
#include <iostream>

void sMovement(Game* gameCtx, float deltaTime) {
  auto& entities = gameCtx->getEntityManager()->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CVelocity>() && e->hasComponent<CTransform>()) {
      auto& transform = e->getComponent<CTransform>();
      auto& velocity = e->getComponent<CVelocity>();

      velocity.velocity.print("v");

      transform.position += velocity.velocity * deltaTime;
    }
  }
}
