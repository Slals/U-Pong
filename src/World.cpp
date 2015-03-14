#include "World.h"
#include "Game.h"

World::World()
{
    sf::IntRect txt(0, 0, 1920, 830);
    _view_world.setTexture(ResourceManager::getInstance().getWorldTexture());
    _view_world.setTextureRect(txt);
    _view_world.setColor(sf::Color::Green);
    _view_world.setPosition(0, 125);
}

void World::render()
{
    Game::getInstance().getWindow().draw(_view_world);
}

sf::IntRect const& World::getBound() const
{
    sf::IntRect bound;

	bound.left = (int)_view_world.getPosition().x;
	bound.width = (int)_view_world.getGlobalBounds().width;
	bound.top = (int)_view_world.getPosition().y;
	bound.height = (int)_view_world.getGlobalBounds().height;

	return bound;
}
