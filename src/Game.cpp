#include "Game.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <iostream>

void Game::initVars() {
  m_window = nullptr;
  m_isLeftMouseDown = false;
}

void Game::initWindow() {
  m_videoMode = sf::VideoMode({800, 600});
  m_window = new sf::RenderWindow(m_videoMode, "My game",
                                  sf::Style::Titlebar | sf::Style::Close);

  m_window->setFramerateLimit(60);
}

Game::Game() {
  initVars();
  initWindow();
  spawnPlayer();
}

Game::~Game() { delete m_window; }

void Game::run() {
  sf::Clock clock;
  while (getIsRunning()) {
    const float dt = clock.restart().asSeconds();
    m_entityManager.update();
    pollEvents();
    updateMousePosition();
    sInput();
    sShootGun(dt);
    sMovement(dt);
    sRender();
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

void Game::updateMousePosition() {
  m_mousePosWindow = sf::Mouse::getPosition(*m_window);

  m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
  // std::cout << "Mouse pos: (" << mousePos.x << ", " << mousePos.y
  // << ")" << std::endl;
}

void Game::spawnPlayer() {
  auto e = m_entityManager.createEntity("player");
  float sizeX = 100.f;
  float sizeY = 100.f;
  float xPos = static_cast<float>(m_window->getSize().x) / 2 - sizeX / 2;
  float yPos = static_cast<float>(m_window->getSize().y) / 2 - sizeY / 2;

  e->addComponent<CTransform>(Vec2(xPos, yPos));
  e->addComponent<CRectShape>(Vec2(sizeX, sizeY), sf::Color::Red,
                              sf::Color::Black, 2.f);
  e->addComponent<CInput>();
  e->addComponent<CShoot>(0.5f);
}

void Game::spawnBullet(Vec2& startPos) {
  auto e = m_entityManager.createEntity("player");

  e->addComponent<CTransform>(startPos);
  e->addComponent<CRectShape>(Vec2(10.f, 10.f), sf::Color::Green,
                              sf::Color::Black, 2.f);
  e->addComponent<CInput>();
  auto& vc = e->addComponent<CVelocity>();
  vc.velocity.x = 200.f;
}

void Game::sInput() {
  auto& entities = m_entityManager.getEntities("player");

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

void Game::sShootGun(float dt) {
  auto& entities = m_entityManager.getEntities("player");

  for (auto& e : entities) {
    if (e->hasComponent<CShoot>()) {
      auto& cs = e->getComponent<CShoot>();

      std::cout << "pressing shoot " << cs.timeSinceLastShot << " "
                << cs.delayBetweenShots << std::endl;
      if (cs.timeSinceLastShot >= cs.delayBetweenShots) {
        if (e->hasComponent<CTransform>() && e->hasComponent<CInput>() &&
            e->getComponent<CInput>().shoot) {
          cs.timeSinceLastShot = 0;
          spawnBullet(e->getComponent<CTransform>().position);
        }
      } else {
        cs.timeSinceLastShot += dt;
      }
    }
  }
}

void Game::sMovement(float deltaTime) {
  auto& entities = m_entityManager.getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CVelocity>() && e->hasComponent<CTransform>()) {
      auto& transform = e->getComponent<CTransform>();
      auto& velocity = e->getComponent<CVelocity>();

      transform.position += velocity.velocity * deltaTime;
    }
  }
}

void Game::sRender() {
  m_window->clear(sf::Color::Cyan);

  auto& entities = m_entityManager.getEntities();

  for (auto& e : entities) {
    if (e->hasComponent<CRectShape>() && e->hasComponent<CTransform>()) {
      auto& cs = e->getComponent<CRectShape>();
      auto& ct = e->getComponent<CTransform>();
      cs.shape.setPosition(sf::Vector2f(ct.position.x, ct.position.y));
      cs.shape.setSize(sf::Vector2f(cs.size.x, cs.size.y));
      cs.shape.setFillColor(cs.color);
      cs.shape.setOutlineColor(cs.outlineColour);
      cs.shape.setOutlineThickness(cs.outlineThickness);
      m_window->draw(cs.shape);
    }
  }

  m_window->display();
}

bool Game::getIsRunning() const { return m_window->isOpen(); }
