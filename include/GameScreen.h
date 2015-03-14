#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <memory>
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "AIPaddle.h"
#include "PPaddle.h"
#include "Screen.h"
#include "CollisionManager.h"
#include "World.h"
#include "UI.h"

enum GameMode
{
	STANDART
};

class GameScreen : public Screen
{
	public:
		GameScreen(GameMode mode = GameMode::STANDART);
		virtual ~GameScreen();

		void render();
		void update(sf::Time delta);
		void handleInput();

	private:
		std::vector<std::shared_ptr<Entity>> _entities;
		CollisionManager _col_mng;
		std::shared_ptr<World> _world;
		UI _ui;

		void createEntities(GameMode mode);
		void initCollideManager();
		void initWorld();
};

#endif // GAMESCREEN_H
