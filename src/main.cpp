#include "engine/core/Game.hpp"
#include "game/scenes/MenuScene.hpp"

int main() {
  Game game;
  game.setScene<MenuScene>();
  game.run();

  return 0;
}
