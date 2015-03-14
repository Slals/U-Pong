#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main(int argc, char *argv[])
{
	Game& game = Game::getInstance();
	game.run();

	return EXIT_SUCCESS;
}
