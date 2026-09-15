#include "Game.hpp"
#include "Entity.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Mouse.hpp>
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
  auto e = m_entityManger.createEntity("player");
  e->addComponent<CTransform>();
  e->addComponent<CRectShape>(Vec2(100, 100), sf::Color::Red, sf::Color::Black,
                              2.f);
  m_entityManger.update();

  m_entityManger.printSize();
  initVars();
  initWindow();
}

Game::~Game() { delete m_window; }

void Game::run() {
  while (getIsRunning()) {
    m_entityManger.update();
    m_entityManger.printSize();
    pollEvents();
    updateMousePosition();
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

void Game::sRender() {
  m_window->clear(sf::Color::Cyan);

  auto entities = m_entityManger.getEntities();

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
