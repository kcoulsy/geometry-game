#include "MenuScene.hpp"
#include "../../Systems.hpp"
#include "GameScene.hpp"

bool MenuScene::init() {
  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    return false;
  }

  getEntityManager()->createEntity("ui")->addComponents(CUIText("Press Space to start"));
  getEntityManager()->printSize();

  return true;
}

void MenuScene::update(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    m_sceneManager->goToScene(new GameScene(getWindow()));
  }
  getEntityManager()->update();
  getWindow()->clear(sf::Color::Black);
  sRenderUI(this);
  getWindow()->display();
}

bool MenuScene::close() { return true; }
