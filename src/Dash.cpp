#include "Dash.h"

Dash::Dash()
{
	//ctor
}

Dash::Dash(float cooldown)
{
	_cooldown = cooldown;
    _current_cd = 0;
}

void Dash::launch()
{
	_current_cd = _cooldown;
	_active = true;
}

void Dash::update(Entity* entity, sf::Time delta)
{
	if(_duration < 150)
	{
		if(((Paddle*)entity)->getVelocity().y < 0)
			((Paddle*)entity)->setVelocity(-1);
		else
			((Paddle*)entity)->setVelocity(1);
		float velocity = ((Paddle*)entity)->getVelocity().y * 2.5 * delta.asMilliseconds();
		((Paddle*)entity)->setVelocity(velocity);
		_duration += delta.asMilliseconds();
	}
	else
	{
		_duration = 0;
		_active = false;
	}
}

bool Dash::isActive()
{
    return _active;
}
