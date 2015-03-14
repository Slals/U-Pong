#include "Paddle.h"
#include "Game.h"

Paddle::Paddle(std::shared_ptr<World>& world, unsigned int const id, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield):
	_id(id)
{
	_view_paddle.setTexture(ResourceManager::getInstance().getPaddleTexture());
	_view_paddle.setPosition(pos);

	initViews(id);

	Entity::_type = Object::PADDLE;

	_skills.push_back(std::unique_ptr<Skill>(new Reverse(10.f)));
	_skills.push_back(std::unique_ptr<Skill>(new Dash(2.f)));

    _world = world;
	_velocity = sf::Vector2f(0, 0);

	_view_paddle.setOrigin(_view_paddle.getGlobalBounds().width / 2, _view_paddle.getGlobalBounds().height / 2);

	_shield = shield;
}

void Paddle::update(sf::Time delta)
{
	_view_paddle.setPosition(_view_paddle.getPosition().x, _view_paddle.getPosition().y + _velocity.y);

	if(_skills.at(1)->isActive())
	{
		_skills.at(1)->update((Paddle*)this, delta);
	}
	else
	{
		_velocity.y = 0;
	}

    if(_skills.at(0)->isActive())
        _skills.at(0)->update((Paddle*)this, delta);

    _skills.at(0)->updateCD(delta);
    _skills.at(1)->updateCD(delta);
}

void Paddle::render()
{
	Game::getInstance().getWindow().draw(_view_paddle);
}

void Paddle::moveUp(sf::Time delta)
{
    _velocity.y = _speed * delta.asMilliseconds() * (-1);
}

void Paddle::moveDown(sf::Time delta)
{
    _velocity.y = _speed * delta.asMilliseconds();
}

void Paddle::onWorldCollision()
{
    sf::IntRect ebound(getBound()), wbound(_world->getBound());
    //int eright = ebound.left + ebound.width;
    int ebottom = ebound.top + ebound.height;
    //int wright = wbound.left + wbound.height;
    int wbottom = wbound.top + wbound.height;

    if(ebound.top < wbound.top)
        _view_paddle.setPosition(_view_paddle.getPosition().x, wbound.top + (ebound.height / 2));
    else if(ebottom > wbottom)
        _view_paddle.setPosition(_view_paddle.getPosition().x, wbottom - (ebound.height / 2));

}

void Paddle::onObjectCollision(std::shared_ptr<Entity>& entity)
{

}

sf::IntRect const& Paddle::getBound() const
{
	sf::IntRect bound;

	bound.left = (int)_view_paddle.getPosition().x - (_view_paddle.getGlobalBounds().width / 2);
	bound.width = (int)_view_paddle.getGlobalBounds().width;
	bound.top = (int)_view_paddle.getPosition().y - (_view_paddle.getGlobalBounds().height / 2);
	bound.height = (int)_view_paddle.getGlobalBounds().height;

	return bound;
}

void Paddle::initViews(unsigned int const id)
{
	switch(id)
    {
		case 1:
			_view_paddle.setTextureRect(sf::IntRect(0, 0, 30, 175));
			break;
		case 2:
			_view_paddle.setTextureRect(sf::IntRect(0, 0, 30, 175));
			break;

    }
}

void Paddle::rotate(unsigned int degree)
{
	_view_paddle.setRotation(_view_paddle.getRotation() + degree);
}

void Paddle::reverseState()
{
	_state = !_state;
	if(isAtkState())
		_view_paddle.setRotation(0);
	else
		_view_paddle.setRotation(180);
}

void Paddle::setVelocity(float value)
{
	_velocity.y = value;
}
