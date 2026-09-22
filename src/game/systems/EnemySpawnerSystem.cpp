#include "../components/Components.hpp"
#include "Systems.hpp"
#include <cstdlib>

void sEnemySpawner(Scene* scene, EntityFactory& factory, float deltaTime) {
  auto em = scene->getEntityManager();
  for (auto e : em->getEntities("enemy_manager")) {
    if (!e->hasComponent<CEnemyManager>())
      continue;

    auto& cem = e->getComponent<CEnemyManager>();

    if (cem.timeSinceLastSpawn <= cem.spawnInterval) {
      cem.timeSinceLastSpawn += deltaTime;
    } else {
      if (em->getEntities("enemies").size() < cem.maxEnemies) {
        auto window = scene->getWindow();
        factory.createEnemy(rand() % window->getSize().x, rand() % window->getSize().y);
        cem.currentEnemyCount++;
        cem.timeSinceLastSpawn = 0;
      } else {
        cem.timeSinceLastSpawn += deltaTime;
      }
    }
  }
}
