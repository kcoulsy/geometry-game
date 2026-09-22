#include "Systems.hpp"
#include "Component.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

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

void sInput(Game* gameCtx) {
  auto& entities = gameCtx->getEntityManager()->getEntities("player");

  for (auto& e : entities) {
    if (e->hasComponent<CInput>()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        e->getComponent<CInput>().shoot = true;
      } else {
        e->getComponent<CInput>().shoot = false;
      }
    }
  }
}

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

void sMovement(Game* gameCtx, float deltaTime) {
  auto& entities = gameCtx->getEntityManager()->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CVelocity>() && e->hasComponent<CTransform>()) {
      auto& transform = e->getComponent<CTransform>();
      auto& velocity = e->getComponent<CVelocity>();

      // velocity.velocity.print("v");

      transform.position += velocity.velocity * deltaTime;
    }
  }
}

void sPhysics(Game* gameCtx, float deltaTime) {
  auto window = gameCtx->getWindow();
  auto& em = gameCtx->getEntityManager()->getEntities("enemies");

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

          gameCtx->spawnBullet(e->getComponent<CTransform>().position, mouseVec, cs.bulletSpeed);
        }
      } else {
        cs.timeSinceLastShot += deltaTime;
      }
    }
  }
}

void sRender(Game* gameCtx) {
  auto em = gameCtx->getEntityManager();
  auto window = gameCtx->getWindow();
  window->clear(sf::Color::Cyan);

  auto& entities = em->getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CRectShape>() && e->hasComponent<CTransform>()) {
      auto& cs = e->getComponent<CRectShape>();
      auto& ct = e->getComponent<CTransform>();
      cs.shape.setOrigin(sf::Vector2f(cs.size.x / 2, cs.size.y / 2));
      cs.shape.setPosition(sf::Vector2f(ct.position.x, ct.position.y));
      cs.shape.setSize(sf::Vector2f(cs.size.x, cs.size.y));
      cs.shape.setFillColor(cs.color);
      cs.shape.setOutlineColor(cs.outlineColour);
      cs.shape.setOutlineThickness(cs.outlineThickness);
      window->draw(cs.shape);
    }
    if (e->hasComponent<CPolyShape>() && e->hasComponent<CTransform>()) {
      auto& cs = e->getComponent<CPolyShape>();
      auto& ct = e->getComponent<CTransform>();
      // cs.shape.setOrigin(sf::Vector2f(cs.size.x / 2, cs.size.y / 2));
      cs.shape.setPosition(sf::Vector2f(ct.position.x, ct.position.y));
      cs.shape.setPointCount(cs.sides);
      cs.shape.setRadius(cs.radius);
      cs.shape.setFillColor(cs.color);
      cs.shape.setOutlineColor(cs.outlineColour);
      cs.shape.setOutlineThickness(cs.outlineThickness);
      window->draw(cs.shape);
    }
    if (e->hasComponent<CBoundingBox>()) {
      auto& cbb = e->getComponent<CBoundingBox>();
      if (cbb.debug) {
        auto& ct = e->getComponent<CTransform>();
        cbb.debugShape.setOrigin(sf::Vector2f(cbb.width / 2, cbb.height / 2));
        cbb.debugShape.setSize(sf::Vector2f(cbb.width, cbb.height));
        cbb.debugShape.setPosition(
            sf::Vector2f(ct.position.x + cbb.offset.x, ct.position.y + cbb.offset.y));
        cbb.debugShape.setFillColor(sf::Color::Transparent);
        cbb.debugShape.setOutlineColor(sf::Color::Red);
        cbb.debugShape.setOutlineThickness(2.f);
        window->draw(cbb.debugShape);
      }
    }
  }

  window->display();
}

bool isCollidingWith(Vec2 aPos, Vec2 aSize, Vec2 bPos, Vec2 bSize) {
  return (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x && aPos.y < bPos.y + bSize.y &&
          aPos.y + aSize.y > bPos.y);
}

void sBulletCollision(Game* gameCtx) {
  auto& bullets = gameCtx->getEntityManager()->getEntities("bullet");
  auto& enemies = gameCtx->getEntityManager()->getEntities("enemies");

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
            std::cout << "hit\n";
            enemyEnt->destroy();
            bulletEnt->destroy();
          }
        }
      }
    }
  }
}