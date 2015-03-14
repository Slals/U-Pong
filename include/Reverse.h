#ifndef REVERSE_H
#define REVERSE_H

#include "Skill.h"
#include "Paddle.h"

class Reverse : public Skill
{
    public:
        Reverse();
        Reverse(float cooldown);
        void launch();
        bool isActive();
        void update(Entity* entity, sf::Time delta);

};

#endif // REVERSE_H
