#include "Shield.h"
#include "Game.h"

Shield::Shield(sf::Vector2f const& pos)
{
	_view_shield.setTexture(ResourceManager::getInstance().getShieldTexture());

	_view_shield.setTextureRect(sf::IntRect(0, 0, 20, 1080));

	_view_shield.setPosition(pos);

	_type = Object::SHIELD;
}

void Shield::render()
{
	Game::getInstance().getWindow().draw(_view_shield);
}

void Shield::update(sf::Time delta)
{

}

void Shield::onWorldCollision()
{

}

void Shield::onObjectCollision(std::shared_ptr<Entity>& entity)
{

}

sf::IntRect const& Shield::getBound() const
{
	sf::IntRect bound;

	bound.left = (int)_view_shield.getPosition().x;
	bound.width = (int)_view_shield.getGlobalBounds().width;
	bound.top = (int)_view_shield.getPosition().y;
	bound.height = (int)_view_shield.getGlobalBounds().height;

	return bound;
}

void Shield::upCharge(unsigned int value)
{

}

void Shield::downCharge(unsigned int value)
{

}

