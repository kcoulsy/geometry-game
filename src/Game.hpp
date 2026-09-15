#pragma once

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
#include <vector>

class Game {
  private:
    sf::RenderWindow *window;
    sf::VideoMode videoMode;

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    unsigned int points;

    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    bool isLeftMouseDown;

    void initVars();
    void initWindow();
    void initEnemies();

  public:
    Game();
    virtual ~Game();

    bool getIsRunning() const;
    void pollEvents();
    void updateMousePosition();
    void update();
    void render();
    void spawnEnemy();
    void updateEnemies();
    void renderEnemies();
};