#include "Game.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Systems/Input.hpp"
#include "Systems/Lifetime.hpp"
#include "Systems/Movement.hpp"
#include "Systems/PlayerShoot.hpp"
#include "Systems/Render.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Game::Game() {
  m_window = nullptr;
  m_videoMode = sf::VideoMode({800, 600});
  m_window = new sf::RenderWindow(m_videoMode, "My game",
                                  sf::Style::Titlebar | sf::Style::Close);

  m_window->setFramerateLimit(60);

  spawnPlayer();
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
    sMovement(this, dt);
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
  auto e = m_entityManager.createEntity("player");
  float sizeX = 100.f;
  float sizeY = 100.f;
  float xPos = static_cast<float>(m_window->getSize().x) / 2;
  float yPos = static_cast<float>(m_window->getSize().y) / 2;

  e->addComponent<CTransform>(Vec2(xPos, yPos));
  e->addComponent<CPolyShape>(5.f, sf::Color::Red, sf::Color::Black, 2.f, 5);
  e->addComponent<CInput>();
  e->addComponent<CShoot>(0.1f, 150.f);
}

void Game::spawnBullet(Vec2& startPos, Vec2 towards, float speed) {
  auto e = m_entityManager.createEntity("bullet");

  e->addComponent<CTransform>(startPos);
  e->addComponent<CRectShape>(Vec2(10.f, 10.f), sf::Color::Green,
                              sf::Color::Black, 2.f);
  e->addComponent<CInput>();
  auto& vc = e->addComponent<CVelocity>();

  vc.velocity += (towards - startPos).normalize() * speed;

  e->addComponent<CLifetime>(2.f);
}

bool Game::getIsRunning() const { return m_window->isOpen(); }

sf::RenderWindow* Game::getWindow() { return m_window; }
EntityManager* Game::getEntityManager() { return &m_entityManager; }