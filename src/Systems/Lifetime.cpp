#include "Lifetime.hpp"

void sLifetime(Game* gameCtx, float deltaTime) {
  auto& entities = gameCtx->getEntityManager()->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CLifetime>()) {
      auto& cl = e->getComponent<CLifetime>();

      if (cl.timeAlive <= cl.timeUntilDestroy) {
        cl.timeAlive += deltaTime;
      } else {
        e->destroy();
      }
    }
  }
}
