#include "../../Component.hpp"
#include "Systems.hpp"
#include <SFML/Window/Keyboard.hpp>

void sInput(Scene* scene) {
  auto& entities = scene->getEntityManager()->getEntities("player");

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
