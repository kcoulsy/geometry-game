#pragma once

#include "Entities.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class SceneManger;

class Scene {
protected:
  EntityManager m_entityManager;
  EntityFactory* m_entities;
  sf::RenderWindow* m_window;
  SceneManger* m_sceneManager;
  sf::Font m_font;

public:
  virtual ~Scene() = default;
  Scene(sf::RenderWindow* window) : m_window(window) {
    m_entities = new EntityFactory(&m_entityManager);
  }
  EntityManager* getEntityManager();
  EntityFactory* getEntityFactory();
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

class GameScene : public Scene {
public:
  using Scene::Scene;
  bool init() override;
  void update(float dt) override;
  bool close() override;
};

class MenuScene : public Scene {

public:
  using Scene::Scene;
  bool init() override;
  void update(float dt) override;
  bool close() override;
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