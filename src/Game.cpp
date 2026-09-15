#include "Game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <iostream>

void Game::initVars() {
    this->window = nullptr;
    this->points = 0;
    this->maxEnemies = 3;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->isLeftMouseDown = false;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode({800, 600});
    this->window =
        new sf::RenderWindow(this->videoMode, "My game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(200.0f, 200.0f));
    this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    this->enemy.setFillColor(sf::Color::Red);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(2.0f);
}

Game::Game() {
    this->initVars();
    this->initWindow();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}

void Game::pollEvents() {
    while (const std::optional event = this->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                window->close();
            }
        }
    }
}

void Game::updateMousePosition() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
    // std::cout << "Mouse pos: (" << this->mousePos.x << ", " << this->mousePos.y << ")" <<
    // std::endl;
}

void Game::update() {
    this->pollEvents();
    this->updateMousePosition();
    this->updateEnemies();
}

void Game::render() {
    this->window->clear(sf::Color::Cyan);

    this->renderEnemies();

    this->window->display();
}

bool Game::getIsRunning() const {
    return this->window->isOpen();
}

void Game::spawnEnemy() {
    float x = static_cast<float>(
        rand() % static_cast<int>((this->window->getSize().x - this->enemy.getSize().x)));
    float y = 0.f;

    std::cout << "Spawning enemy " << x << ", " << y << std::endl;
    this->enemy.setPosition(sf::Vector2f(x, y));

    this->enemy.setFillColor(sf::Color::Red);
    this->enemies.push_back(this->enemy);
}

void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}

void Game::updateEnemies() {
    std::printf("timer %f \n", this->enemySpawnTimer);
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < this->enemies.size(); i++) {
        this->enemies[i].move(sf::Vector2f(0.f, 5.f));

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->points += 1.f;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (this->isLeftMouseDown == false) {
            bool deleted = false;
            this->isLeftMouseDown = true;

            for (int i = 0; i < this->enemies.size() && deleted == false; i++) {
                if ((this->enemies[i].getGlobalBounds().contains(this->mousePosView))) {
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    this->points += 1.f;
                }
            }
        }
    } else {
        this->isLeftMouseDown = false;
    }
}