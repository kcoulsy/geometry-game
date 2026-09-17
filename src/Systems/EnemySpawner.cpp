#include "EnemySpawner.hpp"

void sEnemySpawner(Game* gameCtx, float deltaTime) {
  auto em = gameCtx->getEntityManager();
  for (auto e : em->getEntities("enemy_manager")) {
    if (e->hasComponent<CEnemyManager>()) {
      auto& cem = e->getComponent<CEnemyManager>();

      if (cem.timeSinceLastSpawn <= cem.spawnInterval) {
        cem.timeSinceLastSpawn += deltaTime;
      } else {
        if (em->getEntities("enemies").size() < cem.maxEnemies) {

          gameCtx->spawnEnemy();
          cem.currentEnemyCount++;
          cem.timeSinceLastSpawn = 0;
        } else {
          cem.timeSinceLastSpawn += deltaTime;
        }
      }
    }
  }
}