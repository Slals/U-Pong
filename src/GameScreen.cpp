#include "GameScreen.h"

#include <iostream>

GameScreen::GameScreen(GameMode mode)
{
    initWorld();
	createEntities(mode);
	initCollideManager();
}

GameScreen::~GameScreen()
{
	//dtor
}

void GameScreen::render()
{
    _world->render();
	for(auto entity : _entities)
		entity->render();
	_ui.render();
}

void GameScreen::update(sf::Time delta)
{
	for(auto entity : _entities)
    {
		entity->update(delta);
		_col_mng.checkAllCollisions(entity);
    }
    _ui.update();
}

void GameScreen::handleInput()
{

}

void GameScreen::createEntities(GameMode mode)
{
	ResourceManager::getInstance().loadGameTexture();
	switch(mode)
	{
		case STANDART:
			std::shared_ptr<Shield> shield1 = std::make_shared<Shield>(sf::Vector2f(30, 0));
			std::shared_ptr<Shield> shield2 = std::make_shared<Shield>(sf::Vector2f(1860, 0));
			_entities.push_back(std::make_shared<PPaddle>(_world, 1, sf::Vector2f(200, 540), shield1));
			_entities.push_back(std::make_shared<AIPaddle>(_world, 2, sf::Vector2f(1720, 540), shield2));
			_entities.push_back(std::make_shared<Ball>(_world));
			_entities.push_back(shield1);
			_entities.push_back(shield2);
			break;
	}

}

void GameScreen::initCollideManager()
{
    _col_mng.initEntities(_entities);
    _col_mng.initWorld(_world);
}

void GameScreen::initWorld()
{
    _world = std::make_shared<World>();
}
