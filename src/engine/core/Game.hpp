#pragma once

#include "SceneManager.hpp"
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
  SceneManager m_sceneManager;

  bool getIsRunning() const;
  void pollEvents();

public:
  Game();
  virtual ~Game();

  sf::RenderWindow* getWindow();

  // The engine cannot know which scene a game starts on. The game names the
  // scene type here and the engine constructs it with the window.
  template <typename SceneT>
  void setScene() {
    m_sceneManager.goToScene(new SceneT(m_window));
  }

  void run();
};