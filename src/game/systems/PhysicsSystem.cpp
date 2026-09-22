#include "../../Component.hpp"
#include "Systems.hpp"

void sPhysics(Scene* scene, float deltaTime) {
  auto window = scene->getWindow();
  auto& em = scene->getEntityManager()->getEntities("enemies");

  for (auto& e : em) {
    auto& t = e->getComponent<CTransform>();
    auto& bb = e->getComponent<CBoundingBox>();
    auto& v = e->getComponent<CVelocity>();

    // left
    if ((t.position.x) <= 0.f) {
      v.velocity.x = -v.velocity.x;
    }
    // right
    if ((t.position.x + bb.width / 2 + bb.offset.x) > window->getSize().x) {
      v.velocity.x = -v.velocity.x;
    }
    // top
    if ((t.position.y) <= 0) {
      v.velocity.y = -v.velocity.y;
    }
    // bottom
    if ((t.position.y + bb.height / 2 + bb.offset.y) > window->getSize().y) {
      v.velocity.y = -v.velocity.y;
    }
  }
}
