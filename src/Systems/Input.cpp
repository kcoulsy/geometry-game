#include "Input.hpp"

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