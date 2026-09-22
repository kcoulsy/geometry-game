#pragma once

#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>

class Game {
private:
  sf::RenderWindow* m_window;
  sf::VideoMode m_videoMode;
  EntityManager m_entityManager;
  sf::Font m_font;

  bool getIsRunning() const;
  void pollEvents();

public:
  Game();
  virtual ~Game();

  sf::RenderWindow* getWindow();
  EntityManager* getEntityManager();
  sf::Font* getFont();

  void spawnPlayer();
  void spawnBullet(Vec2& startPos, Vec2 towards, float speed);
  void spawnEnemy();

  void run();
};