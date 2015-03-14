#ifndef DASH_H
#define DASH_H

#include "Skill.h"
#include "Paddle.h"

class Dash : public Skill
{
	public:
		Dash();
		Dash(float cooldown);
        void launch();
        bool isActive();
        void update(Entity* entity, sf::Time delta);

	private:
		float _duration = 0;

};

#endif // DASH_H
