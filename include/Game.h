#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>
#include <math.h>

#include "GameScreen.h"

#define PI 3.14159265

class Game
{
	public:
		static Game& getInstance();

		void run();
		void render();
		void changeWinSize(unsigned int width, unsigned int height);

		sf::RenderWindow& getWindow() { return _window; };

		static std::shared_ptr<Screen> SCREEN;

	private:
	    Game& operator=(const Game&) { };
		Game (const Game&) { };

		static Game _game_instance;
		Game();
		~Game();

		sf::RenderWindow _window;

		void handleInput();

};

#endif // GAME_H
