#include "../components/Components.hpp"
#include "../../engine/math/Vec2.hpp"
#include "Systems.hpp"
#include <format>
#include <iostream>

namespace {

bool isCollidingWith(Vec2 aPos, Vec2 aSize, Vec2 bPos, Vec2 bSize) {
  return (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x && aPos.y < bPos.y + bSize.y &&
          aPos.y + aSize.y > bPos.y);
}

} // namespace

void sBulletCollision(Scene* scene) {
  auto& bullets = scene->getEntityManager()->getEntities("bullet");
  auto& enemies = scene->getEntityManager()->getEntities("enemies");
  auto& uis = scene->getEntityManager()->getEntities("ui");

  for (auto bulletEnt : bullets) {
    if (bulletEnt->hasComponent<CBoundingBox>()) {
      CBoundingBox& bulletBB = bulletEnt->getComponent<CBoundingBox>();
      CTransform& bulletT = bulletEnt->getComponent<CTransform>();

      for (auto enemyEnt : enemies) {
        if (enemyEnt->hasComponent<CBoundingBox>()) {
          CBoundingBox& enemyBB = enemyEnt->getComponent<CBoundingBox>();
          CTransform& enemyT = enemyEnt->getComponent<CTransform>();

          if (isCollidingWith(bulletT.position,
                              Vec2(bulletBB.width, bulletBB.height),
                              enemyT.position,
                              Vec2(enemyBB.width, enemyBB.height))) {

            enemyEnt->destroy();
            bulletEnt->destroy();

            for (auto uiEnt : uis) {
              if (uiEnt->hasComponent<CScore>() && uiEnt->hasComponent<CUIText>()) {
                auto& s = uiEnt->getComponent<CScore>();
                s.score = s.score + 1;
                std::cout << s.score << std::endl;
                uiEnt->getComponent<CUIText>().text = std::format("Score: {}", s.score);
              }
            }
          }
        }
      }
    }
  }
}
