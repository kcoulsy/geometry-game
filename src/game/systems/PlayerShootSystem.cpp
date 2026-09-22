#include "../components/Components.hpp"
#include "../../engine/math/Vec2.hpp"
#include "Systems.hpp"
#include <SFML/Window/Mouse.hpp>

void sPlayerShoot(Scene* scene, EntityFactory& factory, float deltaTime) {
  auto& entities = scene->getEntityManager()->getEntities("player");
  auto window = scene->getWindow();
  for (auto& e : entities) {
    if (e->hasComponent<CShoot>()) {
      auto& cs = e->getComponent<CShoot>();

      if (cs.timeSinceLastShot >= cs.delayBetweenShots) {
        if (e->hasComponent<CTransform>() && e->hasComponent<CInput>() &&
            e->getComponent<CInput>().shoot) {
          cs.timeSinceLastShot = 0;

          auto p = sf::Mouse::getPosition(*window);
          auto mp = window->mapPixelToCoords(p);
          Vec2 mouseVec = Vec2(mp.x, mp.y);

          factory.createBullet(e->getComponent<CTransform>().position, mouseVec, cs.bulletSpeed);
        }
      } else {
        cs.timeSinceLastShot += deltaTime;
      }
    }
  }
}
