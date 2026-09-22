#include "../../engine/math/Collision.hpp"
#include "../../engine/math/Vec2.hpp"
#include "../components/Components.hpp"
#include "Systems.hpp"
#include <format>

void sBulletCollision(Scene* scene) {
  auto& bullets = scene->getEntityManager()->getEntities("bullet");
  auto& enemies = scene->getEntityManager()->getEntities("enemies");
  auto& uis = scene->getEntityManager()->getEntities("ui");

  for (auto bulletEnt : bullets) {
    if (!bulletEnt->hasComponents<CBoundingBox, CTransform>())
      continue;

    CBoundingBox& bulletBB = bulletEnt->getComponent<CBoundingBox>();
    CTransform& bulletT = bulletEnt->getComponent<CTransform>();

    for (auto enemyEnt : enemies) {
      if (!enemyEnt->hasComponents<CBoundingBox, CTransform>())
        continue;

      CBoundingBox& enemyBB = enemyEnt->getComponent<CBoundingBox>();
      CTransform& enemyT = enemyEnt->getComponent<CTransform>();

      if (isCollidingWith(bulletT.position,
                          Vec2(bulletBB.width, bulletBB.height),
                          enemyT.position,
                          Vec2(enemyBB.width, enemyBB.height))) {

        enemyEnt->destroy();
        bulletEnt->destroy();

        for (auto uiEnt : uis) {
          if (!uiEnt->hasComponents<CScore, CUIText>())
            continue;

          auto& s = uiEnt->getComponent<CScore>();
          s.score = s.score + 1;
          uiEnt->getComponent<CUIText>().text = std::format("Score: {}", s.score);
        }
      }
    }
  }
}
