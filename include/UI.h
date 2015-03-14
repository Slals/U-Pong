#ifndef UI_H
#define UI_H

#include "Paddle.h"

class Game;

class UI
{
	public:
		UI();

		void update();
		void render();

	private:
		sf::Sprite _view_UI1;
		sf::Sprite _view_UI2;
};

#endif // UI_H
