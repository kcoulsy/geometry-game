#include "PlayerShoot.hpp"

void sPlayerShoot(Game* gameCtx, float deltaTime) {
  auto& entities = gameCtx->getEntityManager()->getEntities("player");
  auto window = gameCtx->getWindow();
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

          gameCtx->spawnBullet(e->getComponent<CTransform>().position, mouseVec,
                               cs.bulletSpeed);
        }
      } else {
        cs.timeSinceLastShot += deltaTime;
      }
    }
  }
}
