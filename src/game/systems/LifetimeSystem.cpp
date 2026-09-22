#include "../../Component.hpp"
#include "Systems.hpp"

void sLifetime(Scene* scene, float deltaTime) {
  auto& entities = scene->getEntityManager()->getEntities();

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
