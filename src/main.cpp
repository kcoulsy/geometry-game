#include "Game.hpp"
#include <cstdlib>
#include <ctime>

int main() {

    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    while (game.getIsRunning()) {
        game.update();
        game.render();
    }

    return 0;
}
