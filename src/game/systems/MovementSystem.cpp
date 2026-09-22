#include "../../Component.hpp"
#include "Systems.hpp"

void sMovement(Scene* scene, float deltaTime) {
  auto& entities = scene->getEntityManager()->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CVelocity>() && e->hasComponent<CTransform>()) {
      auto& transform = e->getComponent<CTransform>();
      auto& velocity = e->getComponent<CVelocity>();

      transform.position += velocity.velocity * deltaTime;
    }
  }
}
