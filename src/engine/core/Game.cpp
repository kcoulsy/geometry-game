#include "Game.hpp"
#include "../../game/scenes/MenuScene.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Game::Game() {
  m_window = nullptr;
  m_videoMode = sf::VideoMode({800, 600});
  m_window = new sf::RenderWindow(m_videoMode, "My game", sf::Style::Titlebar | sf::Style::Close);
  m_window->setFramerateLimit(60);

  m_sceneManager.goToScene(new MenuScene(m_window));
}

Game::~Game() { delete m_window; }

void Game::run() {
  sf::Clock clock;
  float lastTime = 0;
  while (getIsRunning()) {
    const float dt = clock.restart().asSeconds();
    pollEvents();
    auto scene = m_sceneManager.getCurrent();
    if (scene) {
      scene->update(dt);
    }
    m_sceneManager.resolve();
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
