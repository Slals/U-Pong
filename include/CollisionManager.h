#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "Entity.h"
#include "World.h"
#include "Ball.h"

class CollisionManager
{
    public:
        CollisionManager();

        void initEntities(std::vector<std::shared_ptr<Entity>>& entities);
        void initWorld(std::shared_ptr<World>& world);
        void checkAllCollisions(std::shared_ptr<Entity>& pov_entity);

    private:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::shared_ptr<World> _world;

        bool checkWorldCollision(sf::IntRect const& pov_ebound);
        bool controlObjectCollision(sf::IntRect const& pov_ebound, sf::IntRect const& other_ebound);

};

#endif // COLLISIONMANAGER_H
