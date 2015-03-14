#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "World.h"

enum Object
{
	PADDLE,
	BALL,
	SHIELD
};

class Entity
{
	public:
		virtual void render() = 0;
		virtual void update(sf::Time delta) = 0;
		virtual void onWorldCollision() = 0;
		virtual void onObjectCollision(std::shared_ptr<Entity>& entity) = 0;
        virtual sf::IntRect const& getBound() const = 0;

        Object getType() const { return _type; };

	protected:
		Object _type;
		std::shared_ptr<World> _world;

};

#endif // ENTITY_H_INCLUDED
