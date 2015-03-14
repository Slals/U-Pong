#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

class Game;

class World
{
    public:
        World();

        void render();
        sf::IntRect const& getBound() const;

    private:
        sf::Sprite _view_world;
        float _friction;
};

#endif // WORLD_H
