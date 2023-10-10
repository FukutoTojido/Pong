#include <iostream>
#include "Game.h"
#include <time.h>

int main(int argc, char *argv[])
{
    // Set random seed
    srand(time(NULL));

    // Create game object
    Game game = Game(1024, 720);

    // Initialize game
    if (game.init() < 0)
        return 1;

    // Main loop
    game.loop();

    return 0;
}
