#include "CollisionManager.h"
#include "World.h"

CollisionManager::CollisionManager()
{

}

void CollisionManager::initEntities(std::vector<std::shared_ptr<Entity>>& entities)
{
    _entities = entities;
}

void CollisionManager::initWorld(std::shared_ptr<World>& world)
{
    _world = world;
}

void CollisionManager::checkAllCollisions(std::shared_ptr<Entity>& pov_entity) // point of view from the entity
{
    if(checkWorldCollision(pov_entity->getBound()))
        pov_entity->onWorldCollision();

    sf::IntRect ebound(pov_entity->getBound()), obound;

    for(auto entity : _entities)
    {
        if(entity != pov_entity)
        {
            // First global control for and call a specific one
			obound = entity->getBound();
            if(controlObjectCollision(ebound, obound))
				pov_entity->onObjectCollision(entity);

        }
    }
}

bool CollisionManager::checkWorldCollision(sf::IntRect const& pov_ebound)
{
    sf::IntRect wbound(_world->getBound()), ebound(pov_ebound);

    int ebottom(ebound.top + ebound.height);
    int eright(ebound.left + ebound.width);
    int wbottom(wbound.top + wbound.height);
    int wright(wbound.left + wbound.width);

    if(ebound.top > wbound.top && eright < wright && ebottom < wbottom && ebound.left > wbound.left)
        return false;

    return true;
}

bool CollisionManager::controlObjectCollision(sf::IntRect const& pov_ebound, sf::IntRect const& other_ebound)
{
    if(pov_ebound.intersects(other_ebound))
		return true;

	return false;

}
