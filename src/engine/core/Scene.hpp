#pragma once

#include "../ecs/EntityManager.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SceneManger;

class Scene {
protected:
  EntityManager m_entityManager;
  sf::RenderWindow* m_window;
  SceneManger* m_sceneManager;
  sf::Font m_font;

public:
  virtual ~Scene() = default;
  Scene(sf::RenderWindow* window) : m_window(window) {}

  EntityManager* getEntityManager();
  sf::Font* getFont() { return &m_font; };

  sf::RenderWindow* getWindow() { return m_window; }
  SceneManger* getScreenManager() { return m_sceneManager; }

  bool preInit(SceneManger* screenManager) {
    m_sceneManager = screenManager;
    return true;
  }

  virtual bool init();
  virtual void update(float dt);
  virtual bool close();
};

class SceneManger {
  Scene* m_current = nullptr;
  Scene* m_next = nullptr;

public:
  SceneManger() = default;
  ~SceneManger();
  bool goToScene(Scene* scene);
  void resolve();
  Scene* getCurrent() { return m_current; }
};