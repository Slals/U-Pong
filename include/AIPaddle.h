#ifndef AIPADDLE_H
#define AIPADDLE_H

#include "Paddle.h"

class World;

class AIPaddle : public Paddle
{
    public:
        AIPaddle(std::shared_ptr<World>& world, unsigned int const color, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield);

        void update(sf::Time delta);

    private:

};

#endif // AIPADDLE_H
