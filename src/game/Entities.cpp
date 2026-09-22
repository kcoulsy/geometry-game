#include "Entities.hpp"
#include "components/Components.hpp"

void EntityFactory::createPlayer(float xPos, float yPos) {

  auto e = m_entityManager->createEntity("player");

  e->addComponents(CTransform(Vec2(xPos, yPos)),
                   CPolyShape(12.f, sf::Color::Red, sf::Color::Black, 2.f, 5),
                   CInput(),
                   CShoot(0.1f, 150.f));
}

void EntityFactory::createBullet(Vec2& startPos, Vec2 towards, float speed) {
  m_entityManager->createEntity("bullet")->addComponents(
      CTransform(startPos),
      CRectShape(Vec2(10.f, 10.f), sf::Color::Green, sf::Color::Black, 2.f),
      CInput(),
      CLifetime(2.f),
      CBoundingBox(10.f, 10.f),
      CVelocity((towards - startPos).normalize() * speed));
}

void EntityFactory::createEnemy(float xPos, float yPos) {

  float radius = rand() % 5 * 10.f;
  // int xPos = rand() % m_window->getSize().x;
  // int yPos = rand() % m_window->getSize().y;
  int points = rand() % 5 + 3;
  sf::Color pickedColor = sf::Color::Green;
  switch (points) {
  case 3:
    pickedColor = sf::Color::Blue;
    break;
  case 4:
    pickedColor = sf::Color::Magenta;
    break;
  case 5:
    pickedColor = sf::Color::Red;
    break;
  case 6:
    pickedColor = sf::Color::Yellow;
    break;
  case 7:
    pickedColor = sf::Color::Green;
    break;
  }

  int randX = (rand() % 7) - 7;
  int randY = (rand() % 7) - 7;
  Vec2 initialVelocity = Vec2(static_cast<float>(randX), static_cast<float>(randY)) * 30.f;

  m_entityManager->createEntity("enemies")->addComponents(
      CTransform(Vec2(xPos, yPos)),
      CPolyShape(radius, pickedColor, sf::Color::Black, 2.f, points),
      CInput(),
      CBoundingBox(radius * 2, radius * 2, Vec2(radius, radius)),
      CShoot(0.1f, 150.f),
      CVelocity(initialVelocity));
}

void EntityFactory::createEnemyManger() {
  m_entityManager->createEntity("enemy_manager")->addComponent(CEnemyManager(5000, 0.001f));
}

void EntityFactory::createScoreUI() {
  m_entityManager->createEntity("ui")->addComponents(CUIText("Score: 0"), CScore());
}

void EntityFactory::createDebugUI() {
  m_entityManager->createEntity("ui")->addComponents(
      CTransform(Vec2(0, 100)), CUIText("Debug:"), CDebug());
}