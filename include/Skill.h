#ifndef SKILL_H
#define SKILL_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Game;

class Skill
{
	public:
		virtual void launch() = 0;
		virtual bool isActive() = 0;
		virtual void update(Entity* entity, sf::Time delta) = 0;
		bool isOnCD() const;
		void updateCD(sf::Time delta);

	protected:
		float _cooldown;
		float _current_cd;
		float _duration;
		bool _active = false;
};

#endif // SKILL_H
