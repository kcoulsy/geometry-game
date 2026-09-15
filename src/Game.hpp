#pragma once

#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
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

  sf::Vector2i m_mousePosWindow;
  sf::Vector2f m_mousePosView;

  EntityManager m_entityManger;
  bool m_isLeftMouseDown;

  void initVars();
  void initWindow();

public:
  Game();
  virtual ~Game();

  bool getIsRunning() const;
  void pollEvents();
  void updateMousePosition();
  void run();
  void sMovement(float deltaTime);
  void sRender();
};