#pragma once

#include "Entities.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Scene {
protected:
  EntityManager m_entityManager;
  EntityFactory* m_entities;
  sf::RenderWindow* m_window;

public:
  virtual ~Scene() = default;
  Scene(sf::RenderWindow* window) : m_window(window) {
    m_entities = new EntityFactory(&m_entityManager);
  }
  EntityManager* getEntityManager();
  EntityFactory* getEntityFactory();

  sf::RenderWindow* getWindow() { return m_window; }

  virtual bool init();
  virtual void update(float dt);
  virtual bool close();
};

class GameScene : public Scene {
  sf::Font m_font;

public:
  using Scene::Scene;
  sf::Font* getFont() { return &m_font; };
  bool init() override;
  void update(float dt) override;
  bool close() override;
};