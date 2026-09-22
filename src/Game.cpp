#include "Game.hpp"
#include "Component.hpp"
#include "ECS.hpp"
#include "Entities.hpp"
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
#include <iostream>

Game::Game() {
  m_window = nullptr;
  m_videoMode = sf::VideoMode({800, 600});
  m_window = new sf::RenderWindow(m_videoMode, "My game", sf::Style::Titlebar | sf::Style::Close);
  m_entities = new EntityFactory(&m_entityManager);

  m_window->setFramerateLimit(60);

  if (!m_font.openFromFile("assets/retro-font.ttf")) {
    throw 1;
    // todo some proper handling here
  }

  m_entities->createPlayer(static_cast<float>(m_window->getSize().x) / 2,
                           static_cast<float>(m_window->getSize().y) / 2);
  m_entities->createEnemyManger();
  m_entities->createScoreUI();
  m_entities->createDebugUI();
}

Game::~Game() { delete m_window; }

void Game::run() {
  sf::Clock clock;
  float lastTime = 0;
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
    sDebugUI(this, dt);
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

bool Game::getIsRunning() const { return m_window->isOpen(); }
sf::RenderWindow* Game::getWindow() { return m_window; }
EntityManager* Game::getEntityManager() { return &m_entityManager; }
sf::Font* Game::getFont() { return &m_font; };
EntityFactory* Game::getEntityFactory() { return m_entities; }