#include "Skill.h"
#include "Game.h"

bool Skill::isOnCD() const
{
	return _current_cd > 0;
}

void Skill::updateCD(sf::Time delta)
{
	_current_cd -= delta.asSeconds();
	if(_current_cd < 0)
		_current_cd = 0;
}
