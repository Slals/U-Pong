#include "AIPaddle.h"

AIPaddle::AIPaddle(std::shared_ptr<World>& world, unsigned int const color, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield) :
    Paddle(world, color, pos, shield)
{
    //ctor
}

void AIPaddle::update(sf::Time delta)
{

}
