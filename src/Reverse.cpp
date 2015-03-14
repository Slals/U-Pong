#include "Reverse.h"

Reverse::Reverse()
{

}

Reverse::Reverse(float cooldown)
{
    _cooldown = cooldown;
    _current_cd = 0;
}

void Reverse::launch()
{
	_current_cd = _cooldown;
	_active = true;
}

void Reverse::update(Entity* entity, sf::Time delta)
{
	if(((Paddle*)entity)->isAtkState())
	{
		if(((Paddle*)entity)->getRotation() < 180)
			((Paddle*)entity)->rotate(1.2f * delta.asMilliseconds());
		else if(((Paddle*)entity)->getRotation() >= 180)
		{
            ((Paddle*)entity)->reverseState();
            _active = false;
		}
	}
	else
	{
		if(((Paddle*)entity)->getRotation() >= 180)
			((Paddle*)entity)->rotate(1.2f * delta.asMilliseconds());
		else if(((Paddle*)entity)->getRotation() >= 0)
		{
            ((Paddle*)entity)->reverseState();
            _active = false;
		}
	}
}

bool Reverse::isActive()
{
    return _active;
}
