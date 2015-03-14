#ifndef PPADDLE_H
#define PPADDLE_H

#include "Paddle.h"

class PPaddle : public Paddle
{
    public:
        PPaddle(std::shared_ptr<World>& world, unsigned int const color, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield);

        void update(sf::Time delta);

    private:
         void handleInput(sf::Time delta);
};

#endif // PPADDLE_H
