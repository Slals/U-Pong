#include "PPaddle.h"

PPaddle::PPaddle(std::shared_ptr<World>& world, unsigned int const color, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield) :
    Paddle(world, color, pos, shield)
{
    //ctor
}

void PPaddle::update(sf::Time delta)
{
    handleInput(delta);
    Paddle::update(delta);
}

void PPaddle::handleInput(sf::Time delta)
{
	if(!_skills.at(1)->isActive())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			moveUp(delta);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			moveDown(delta);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !_skills.at(0)->isOnCD())
		_skills.at(0)->launch();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !_skills.at(1)->isOnCD())
		_skills.at(1)->launch();
}
