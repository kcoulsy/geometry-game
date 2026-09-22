#pragma once

#include "../ecs/EntityManager.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SceneManager;

class Scene {
protected:
  EntityManager m_entityManager;
  sf::RenderWindow* m_window;
  SceneManager* m_sceneManager;
  sf::Font m_font;

public:
  virtual ~Scene() = default;
  Scene(sf::RenderWindow* window) : m_window(window) {}

  EntityManager* getEntityManager();
  sf::Font* getFont() { return &m_font; };

  sf::RenderWindow* getWindow() { return m_window; }
  SceneManager* getSceneManager() { return m_sceneManager; }

  bool preInit(SceneManager* sceneManager) {
    m_sceneManager = sceneManager;
    return true;
  }

  virtual bool init();
  virtual void update(float dt);
  virtual bool close();
};
