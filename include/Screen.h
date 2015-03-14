#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SFML/Graphics.hpp>

class Screen
{
	public:
		virtual void render() = 0;
		virtual void update(sf::Time delta) = 0;
		virtual void handleInput() = 0;
};


#endif // SCREEN_H_INCLUDED
