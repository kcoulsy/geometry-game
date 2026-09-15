#include "Game.hpp"
#include "Entity.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Mouse.hpp>

void Game::initVars() {
  window = nullptr;
  isLeftMouseDown = false;
}

void Game::initWindow() {
  videoMode = sf::VideoMode({800, 600});
  window = new sf::RenderWindow(videoMode, "My game",
                                sf::Style::Titlebar | sf::Style::Close);

  window->setFramerateLimit(60);
}

Game::Game() {
  EntityManager em;
  em.printSize();
  auto e = em.createEntity("player");
  em.update();
  em.printSize();
  auto e2 = em.createEntity("bullet");
  em.update();
  em.printSize();
  e2->destroy();
  em.update();

  em.printSize();
  initVars();
  initWindow();
}

Game::~Game() { delete window; }

void Game::run() {
  while (getIsRunning()) {
    update();
    render();
  }
}

void Game::pollEvents() {
  while (const std::optional event = window->pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window->close();
    }
    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        window->close();
      }
    }
  }
}

void Game::updateMousePosition() {
  mousePosWindow = sf::Mouse::getPosition(*window);

  mousePosView = window->mapPixelToCoords(mousePosWindow);
  // std::cout << "Mouse pos: (" << mousePos.x << ", " << mousePos.y
  // << ")" << std::endl;
}

void Game::update() {
  pollEvents();
  updateMousePosition();
}

void Game::render() {
  window->clear(sf::Color::Cyan);

  window->display();
}

bool Game::getIsRunning() const { return window->isOpen(); }
