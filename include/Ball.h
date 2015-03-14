#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Paddle.h"
#include "World.h"

#include <math.h>

class Game;

class Ball : public Entity
{
	public:
		Ball(std::shared_ptr<World>& world, sf::Vector2f const& pos = sf::Vector2f(960, 540), float speed = 1.1f);
		virtual ~Ball();

		sf::CircleShape const& getViewBall() const { return _view_ball; };
		bool isAction() const { return _action; };

		void start();
		void stop();
		void reverseXDirection();
		void reverseYDirection();
		void upSpeed(float value);
		void downSpeed(float value);

		void render();
		void update(sf::Time delta);

		void onWorldCollision();
		void onObjectCollision(std::shared_ptr<Entity>& entity);
		sf::IntRect const& getBound() const;
		void drawLine(std::shared_ptr<Entity>& entity);

	private:
		sf::CircleShape _view_ball;
		float _speed;
		bool _action;
		sf::Vector2f _velocity;

		sf::Vertex _lines_indicators[20][2];
};

#endif // BALL_H
