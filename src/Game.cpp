#include "Game.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Systems.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <cstdlib>

Game::Game() {
  m_window = nullptr;
  m_videoMode = sf::VideoMode({800, 600});
  m_window = new sf::RenderWindow(m_videoMode, "My game", sf::Style::Titlebar | sf::Style::Close);

  m_window->setFramerateLimit(60);

  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    throw 1;
    // todo some proper handling here
  }

  spawnPlayer();
  m_entityManager.createEntity("enemy_manager")->addComponent(CEnemyManager(10, 0.1f));
  m_entityManager.createEntity("ui")->addComponents(CUIText("Score: 0"), CScore());
}

Game::~Game() { delete m_window; }

void Game::run() {
  sf::Clock clock;
  while (getIsRunning()) {
    const float dt = clock.restart().asSeconds();
    m_entityManager.update();
    pollEvents();
    sLifetime(this, dt);
    sInput(this);
    sPlayerShoot(this, dt);
    sBulletCollision(this);
    sPhysics(this, dt);
    sMovement(this, dt);
    sEnemySpawner(this, dt);
    sRender(this);
  }
}

void Game::pollEvents() {
  while (const std::optional event = m_window->pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_window->close();
    }
    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        m_window->close();
      }
    }
  }
}

void Game::spawnPlayer() {
  float xPos = static_cast<float>(m_window->getSize().x) / 2;
  float yPos = static_cast<float>(m_window->getSize().y) / 2;

  m_entityManager.createEntity("player")->addComponents(
      CTransform(Vec2(xPos, yPos)),
      CPolyShape(12.f, sf::Color::Red, sf::Color::Black, 2.f, 5),
      CInput(),
      CShoot(0.1f, 150.f));
}

void Game::spawnBullet(Vec2& startPos, Vec2 towards, float speed) {
  m_entityManager.createEntity("bullet")->addComponents(
      CTransform(startPos),
      CRectShape(Vec2(10.f, 10.f), sf::Color::Green, sf::Color::Black, 2.f),
      CInput(),
      CLifetime(2.f),
      CBoundingBox(10.f, 10.f),
      CVelocity((towards - startPos).normalize() * speed));
}

void Game::spawnEnemy() {
  float radius = rand() % 5 * 10.f;
  int xPos = rand() % m_window->getSize().x;
  int yPos = rand() % m_window->getSize().y;
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

  m_entityManager.createEntity("enemies")->addComponents(
      CTransform(Vec2(xPos, yPos)),
      CPolyShape(radius, pickedColor, sf::Color::Black, 2.f, points),
      CInput(),
      CBoundingBox(radius * 2, radius * 2, Vec2(radius, radius)),
      CShoot(0.1f, 150.f),
      CVelocity(initialVelocity));
}

bool Game::getIsRunning() const { return m_window->isOpen(); }

sf::RenderWindow* Game::getWindow() { return m_window; }
EntityManager* Game::getEntityManager() { return &m_entityManager; }
sf::Font* Game::getFont() { return &m_font; };
