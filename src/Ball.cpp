#include "Ball.h"
#include "Game.h"

Ball::Ball(std::shared_ptr<World>& world, sf::Vector2f const& pos, float speed):
	_view_ball(sf::CircleShape(20, 100)),
	_speed(speed),
	_action(false)
{
	_view_ball.setPosition(pos);
	Entity::_type = Object::BALL;
	_view_ball.setOrigin(_view_ball.getRadius(), _view_ball.getRadius());
	_velocity = sf::Vector2f(1, 1);
	_world = world;
}

Ball::~Ball()
{
	//dtor
}

void Ball::render()
{
	Game::getInstance().getWindow().draw(_view_ball);
}

void Ball::update(sf::Time delta)
{
    // TEMP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
		start();
	}
	else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Z)))
	{
		stop();
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		stop();
		sf::Vector2i local_size(sf::Mouse::getPosition(Game::getInstance().getWindow()));
		_view_ball.setPosition(local_size.x, local_size.y);
	}

    if(isAction())
    {
		float move_x = _velocity.x * delta.asMilliseconds() * _speed;
		float move_y = _velocity.y * delta.asMilliseconds() * _speed;
        _view_ball.setPosition(_view_ball.getPosition().x + move_x, _view_ball.getPosition().y + move_y);
    }
}

void Ball::onWorldCollision()
{
    sf::IntRect ebound(getBound()), wbound(_world->getBound());
    int eright = ebound.left + ebound.width;
    int ebottom = ebound.top + ebound.height;
    int wright = wbound.left + wbound.width;
    int wbottom = wbound.top + wbound.height;

    if(ebound.top < wbound.top)
    {
        _view_ball.setPosition(_view_ball.getPosition().x, wbound.top + _view_ball.getRadius());
        reverseYDirection();
    }
    else if(ebottom > wbottom)
    {
        _view_ball.setPosition(_view_ball.getPosition().x, wbottom - _view_ball.getRadius());
        reverseYDirection();
    }
    else if(eright > wright)
    {
        _view_ball.setPosition(wright  - _view_ball.getRadius(), _view_ball.getPosition().y);
        reverseXDirection();
    }
    else if(ebound.left < wbound.left)
    {
        _view_ball.setPosition(wbound.left + _view_ball.getRadius(), _view_ball.getPosition().y);
        reverseXDirection();
    }
}

void Ball::onObjectCollision(std::shared_ptr<Entity>& entity)
{
	int etop(entity->getBound().top);
	int eleft(entity->getBound().left);
	int eright(eleft + entity->getBound().width);
	int ebottom(etop + entity->getBound().height);

	sf::Vector2f center = _view_ball.getPosition();

	if(entity->getType() == Object::PADDLE || entity->getType() == Object::SHIELD)
	{
		if(center.x < eleft && center.y < etop)
		{
			/*float angle = 180 - 2 * atan((center.x - eleft) / (center.y - etop)) * 180 / PI;

			// avoid OOB
			if(angle < 45)
				_view_ball.setPosition(_view_ball.getPosition().x, etop - _view_ball.getRadius());
			else if(angle == 45)
				_view_ball.setPosition(eleft - _view_ball.getRadius(), etop - _view_ball.getRadius());
			else
				_view_ball.setPosition(eleft - _view_ball.getRadius(), _view_ball.getPosition().y);

			if(center.x + _view_ball.getRadius() > eleft && center.y + _view_ball.getRadius() > etop)
			{
				_velocity.x = cos(angle);
				_velocity.y = sin(angle);
			}*/
			_view_ball.setPosition(eleft - _view_ball.getRadius(), etop - _view_ball.getRadius());
			reverseXDirection();
			reverseYDirection();
		}
		else if(center.x > eright && center.y < etop)
		{
			/*float angle = 180 - 2 * atan((center.x - eright ) / (center.y - etop)) * 180 / PI;

			if(angle < 45)
				_view_ball.setPosition(_view_ball.getPosition().x, etop - _view_ball.getRadius());
			else if(angle == 45)
				_view_ball.setPosition(eright + _view_ball.getRadius(), etop - _view_ball.getRadius());
			else
				_view_ball.setPosition(eright + _view_ball.getRadius(), _view_ball.getPosition().y);

			if(center.x - _view_ball.getRadius() < eright && center.y + _view_ball.getRadius() > etop)
			{
				_velocity.x = cos(angle);
				_velocity.y = sin(angle);
			}*/
			_view_ball.setPosition(eright + _view_ball.getRadius(), etop - _view_ball.getRadius());
			reverseXDirection();
			reverseYDirection();
		}
		else if(center.x > eright && center.y > ebottom)
		{
			/*float angle = 180 - 2 * atan((center.y - ebottom) / (center.x - eright)) * 180 / PI;

			if(angle < 45)
				_view_ball.setPosition(eright + _view_ball.getRadius(), _view_ball.getPosition().y);
			else if(angle == 45)
				_view_ball.setPosition(eright + _view_ball.getRadius(), ebottom + _view_ball.getRadius());
			else
				_view_ball.setPosition(_view_ball.getPosition().x, ebottom + _view_ball.getRadius());

			if(center.x - _view_ball.getRadius() < eright && center.y - _view_ball.getRadius() < ebottom)
			{
				_velocity.x = cos(angle);
				_velocity.y = sin(angle);
			}*/
			_view_ball.setPosition(eright + _view_ball.getRadius(), ebottom + _view_ball.getRadius());
			reverseXDirection();
			reverseYDirection();
		}
		else if(center.x < eleft && center.y > ebottom)
		{
			/*float angle = 180 - 2 * atan((center.y - ebottom) / (center.x - eleft)) * 180 / PI;

			if(center.x + _view_ball.getRadius() > eleft && center.y - _view_ball.getRadius() < ebottom)
			{
				_velocity.x = cos(angle);
				_velocity.y = sin(angle);
			}*/
			_view_ball.setPosition(eleft - _view_ball.getRadius(), ebottom + _view_ball.getRadius());
			reverseXDirection();
			reverseYDirection();
		}
		if(center.x >= eleft && center.y <= etop && center.x <= eright)
		{
			if(center.y + _view_ball.getRadius() > entity->getBound().top)
			{
				_view_ball.setPosition(_view_ball.getPosition().x, etop - _view_ball.getRadius());
				reverseYDirection();
			}
		}
		else if(center.x >= eright && center.y >= etop && center.y <= ebottom)
		{
			if(center.x - _view_ball.getRadius() < entity->getBound().left + entity->getBound().width)
			{
				_view_ball.setPosition(eright + _view_ball.getRadius(), _view_ball.getPosition().y);
				reverseXDirection();
			}
		}
		else if(center.x >= eleft && center.y >= ebottom && center.x <= eright)
		{
			if(center.y - _view_ball.getRadius() < ebottom)
			{
				_view_ball.setPosition(_view_ball.getPosition().x, ebottom + _view_ball.getRadius());
				reverseYDirection();
			}
		}
		else if(center.x <= eleft && center.y >= etop && center.y <= ebottom)
		{
			if(center.x + _view_ball.getRadius() > eleft)
			{
				_view_ball.setPosition(eleft - _view_ball.getRadius(), _view_ball.getPosition().y);
				reverseXDirection();
			}
		}

		if(entity->getType() == Object::PADDLE)
		{
			Paddle* paddle = ((Paddle*)entity.get());
			if(paddle->isAtkState())
			{
				upSpeed(paddle->getPower());
			}
			else
			{
				downSpeed(paddle->getPower());
			}
		}
	}
}

void Ball::start()
{
    _action = true;
}

void Ball::stop()
{
    _action = false;
}

sf::IntRect const& Ball::getBound() const
{
	sf::IntRect bound;

	bound.left = (int)_view_ball.getPosition().x - _view_ball.getRadius();
	bound.width = (int)_view_ball.getGlobalBounds().width;
	bound.top = (int)_view_ball.getPosition().y - _view_ball.getRadius();
	bound.height = (int)_view_ball.getGlobalBounds().height;

	return bound;
}

void Ball::reverseXDirection()
{
    _velocity.x *= -1;
}

void Ball::reverseYDirection()
{
    _velocity.y *= -1;
}

void Ball::upSpeed(float value)
{
	_speed += _speed * value;
}

void Ball::downSpeed(float value)
{
	_speed -= _speed * value;
}

void Ball::drawLine(std::shared_ptr<Entity>& entity)
{
	sf::Vector2f center(getBound().left + _view_ball.getRadius(), getBound().top + _view_ball.getRadius());

	// Horizontal Paddle top
    _lines_indicators[0][0] = sf::Vertex(sf::Vector2f(0, entity->getBound().top));
    _lines_indicators[0][1] = sf::Vertex(sf::Vector2f(Game::getInstance().getWindow().getSize().x, entity->getBound().top));

    // Horizontal Paddle bot
    _lines_indicators[1][0] = sf::Vertex(sf::Vector2f(0, entity->getBound().top + entity->getBound().height));
    _lines_indicators[1][1] = sf::Vertex(sf::Vector2f(Game::getInstance().getWindow().getSize().x, entity->getBound().top + entity->getBound().height));

    // Vertical Paddle left
    _lines_indicators[2][0] = sf::Vertex(sf::Vector2f(entity->getBound().left, 0));
    _lines_indicators[2][1] = sf::Vertex(sf::Vector2f(entity->getBound().left, Game::getInstance().getWindow().getSize().y));

    // Vertical Paddle right
    _lines_indicators[3][0] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, 0));
    _lines_indicators[3][1] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, Game::getInstance().getWindow().getSize().y));

    // Ball vector
    float speed_x = _speed * 100 * _velocity.x;
    float speed_y = _speed * 100 * _velocity.y;
    _lines_indicators[4][0] = sf::Vertex(center);
    _lines_indicators[4][1] = sf::Vertex(sf::Vector2f(center.x + speed_x, center.y + speed_y));
    _lines_indicators[4][0].color = sf::Color::Green;

	// Horizontal Ball top
    _lines_indicators[5][0] = sf::Vertex(sf::Vector2f(0, getBound().top));
    _lines_indicators[5][1] = sf::Vertex(sf::Vector2f(Game::getInstance().getWindow().getSize().x, getBound().top));
    _lines_indicators[5][0].color = sf::Color::Yellow;
    _lines_indicators[5][1].color = sf::Color::Yellow;

    // Horizontal Ball bot
    _lines_indicators[6][0] = sf::Vertex(sf::Vector2f(0, getBound().top + getBound().height));
    _lines_indicators[6][1] = sf::Vertex(sf::Vector2f(Game::getInstance().getWindow().getSize().x, getBound().top + getBound().height));
    _lines_indicators[6][0].color = sf::Color::Yellow;
    _lines_indicators[6][1].color = sf::Color::Yellow;

    // Vertical Ball left
    _lines_indicators[7][0] = sf::Vertex(sf::Vector2f(getBound().left, 0));
    _lines_indicators[7][1] = sf::Vertex(sf::Vector2f(getBound().left, Game::getInstance().getWindow().getSize().y));
    _lines_indicators[7][0].color = sf::Color::Yellow;
    _lines_indicators[7][1].color = sf::Color::Yellow;

    // Vertical Ball right
    _lines_indicators[8][0] = sf::Vertex(sf::Vector2f(getBound().left + getBound().width, 0));
    _lines_indicators[8][1] = sf::Vertex(sf::Vector2f(getBound().left + getBound().width, Game::getInstance().getWindow().getSize().y));
    _lines_indicators[8][0].color = sf::Color::Yellow;
    _lines_indicators[8][1].color = sf::Color::Yellow;


    if(center.x <= entity->getBound().left && center.y <= entity->getBound().top)
	{
		_lines_indicators[9][0] = sf::Vertex(center);
		_lines_indicators[9][1] = sf::Vertex(sf::Vector2f(entity->getBound().left, entity->getBound().top));
		_lines_indicators[10][0] = sf::Vertex(center);
		_lines_indicators[10][1] = sf::Vertex(sf::Vector2f(center.x, entity->getBound().top));
		_lines_indicators[11][0] = sf::Vertex(center);
		_lines_indicators[11][1] = sf::Vertex(sf::Vector2f(entity->getBound().left, center.y));

		if(_lines_indicators[9][0].position.x + _view_ball.getRadius() > _lines_indicators[9][1].position.x && _lines_indicators[9][0].position.y + _view_ball.getRadius() > _lines_indicators[9][1].position.y)
		{
			_lines_indicators[0][0].color = sf::Color::Red;
			_lines_indicators[2][0].color = sf::Color::Red;
		}

	}
	else if(center.x > entity->getBound().left + entity->getBound().width && center.y < entity->getBound().top)
	{
		_lines_indicators[9][0] = sf::Vertex(center);
		_lines_indicators[9][1] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, entity->getBound().top));
		_lines_indicators[10][0] = sf::Vertex(center);
		_lines_indicators[10][1] = sf::Vertex(sf::Vector2f(center.x, entity->getBound().top));
		_lines_indicators[11][0] = sf::Vertex(center);
		_lines_indicators[11][1] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, center.y));
		if(_lines_indicators[9][0].position.x - _view_ball.getRadius() < _lines_indicators[9][1].position.x && _lines_indicators[9][0].position.y + _view_ball.getRadius() > _lines_indicators[9][1].position.y)
		{
			_lines_indicators[0][0].color = sf::Color::Red;
			_lines_indicators[3][0].color = sf::Color::Red;
		}
	}
	else if(center.x > entity->getBound().left + entity->getBound().width && center.y > entity->getBound().top + entity->getBound().height)
	{
		_lines_indicators[9][0] = sf::Vertex(center);
		_lines_indicators[9][1] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, entity->getBound().top + entity->getBound().height));
		_lines_indicators[10][0] = sf::Vertex(center);
		_lines_indicators[10][1] = sf::Vertex(sf::Vector2f(center.x, entity->getBound().top + entity->getBound().height));
		_lines_indicators[11][0] = sf::Vertex(center);
		_lines_indicators[11][1] = sf::Vertex(sf::Vector2f(entity->getBound().left + entity->getBound().width, center.y));
		if(_lines_indicators[9][0].position.x - _view_ball.getRadius() < _lines_indicators[9][1].position.x && _lines_indicators[9][0].position.y - _view_ball.getRadius() < _lines_indicators[9][1].position.y)
		{
			_lines_indicators[3][0].color = sf::Color::Red;
			_lines_indicators[1][0].color = sf::Color::Red;
		}
	}
	else if(center.x < entity->getBound().left && center.y > entity->getBound().top + entity->getBound().height)
	{
		_lines_indicators[9][0] = sf::Vertex(center);
		_lines_indicators[9][1] = sf::Vertex(sf::Vector2f(entity->getBound().left, entity->getBound().top + entity->getBound().height));
		_lines_indicators[10][0] = sf::Vertex(center);
		_lines_indicators[10][1] = sf::Vertex(sf::Vector2f(center.x, entity->getBound().top + entity->getBound().height));
		_lines_indicators[11][0] = sf::Vertex(center);
		_lines_indicators[11][1] = sf::Vertex(sf::Vector2f(entity->getBound().left, center.y));
		if(_lines_indicators[9][0].position.x + _view_ball.getRadius() > _lines_indicators[9][1].position.x && _lines_indicators[9][0].position.y - _view_ball.getRadius() < _lines_indicators[9][1].position.y)
		{
			_lines_indicators[1][0].color = sf::Color::Red;
			_lines_indicators[2][0].color = sf::Color::Red;
		}
	}
	else if(center.x >= entity->getBound().left && center.y <= entity->getBound().top && center.x <= entity->getBound().left + entity->getBound().width)
	{
		_lines_indicators[9][0] = sf::Vertex();
		_lines_indicators[9][1] = sf::Vertex();
		_lines_indicators[10][0] = sf::Vertex();
		_lines_indicators[10][1] = sf::Vertex();
		_lines_indicators[11][0] = sf::Vertex();
		_lines_indicators[11][1] = sf::Vertex();
		if(center.y + _view_ball.getRadius() > entity->getBound().top)
			_lines_indicators[0][0].color = sf::Color::Red;
	}
	else if(center.x > entity->getBound().left + entity->getBound().width && center.y >= entity->getBound().top && center.y <= entity->getBound().top + entity->getBound().height)
	{
		_lines_indicators[9][0] = sf::Vertex();
		_lines_indicators[9][1] = sf::Vertex();
		_lines_indicators[10][0] = sf::Vertex();
		_lines_indicators[10][1] = sf::Vertex();
		_lines_indicators[11][0] = sf::Vertex();
		_lines_indicators[11][1] = sf::Vertex();
		if(center.x - _view_ball.getRadius() < entity->getBound().left + entity->getBound().width)
			_lines_indicators[3][0].color = sf::Color::Red;
	}
	else if(center.x >= entity->getBound().left && center.y >= entity->getBound().top + entity->getBound().height && center.x <= entity->getBound().left + entity->getBound().width)
	{
		_lines_indicators[9][0] = sf::Vertex();
		_lines_indicators[9][1] = sf::Vertex();
		_lines_indicators[10][0] = sf::Vertex();
		_lines_indicators[10][1] = sf::Vertex();
		_lines_indicators[11][0] = sf::Vertex();
		_lines_indicators[11][1] = sf::Vertex();
		if(center.y - _view_ball.getRadius() < entity->getBound().top + entity->getBound().height)
			_lines_indicators[1][0].color = sf::Color::Red;
	}
	else if(center.x <= entity->getBound().left && center.y >= entity->getBound().top && center.y <= entity->getBound().top + entity->getBound().height)
	{
		_lines_indicators[9][0] = sf::Vertex();
		_lines_indicators[9][1] = sf::Vertex();
		_lines_indicators[10][0] = sf::Vertex();
		_lines_indicators[10][1] = sf::Vertex();
		_lines_indicators[11][0] = sf::Vertex();
		_lines_indicators[11][1] = sf::Vertex();
		if(center.x + _view_ball.getRadius() > entity->getBound().left)
			_lines_indicators[2][0].color = sf::Color::Red;
	}
	else
	{
		_lines_indicators[9][0] = sf::Vertex();
		_lines_indicators[9][1] = sf::Vertex();
		_lines_indicators[10][0] = sf::Vertex();
		_lines_indicators[10][1] = sf::Vertex();
		_lines_indicators[11][0] = sf::Vertex();
		_lines_indicators[11][1] = sf::Vertex();
	}
	_lines_indicators[9][0].color = sf::Color::Magenta;
	_lines_indicators[10][0].color = sf::Color::Cyan;
	_lines_indicators[10][1].color = sf::Color::Cyan;
	_lines_indicators[11][0].color = sf::Color::Cyan;
	_lines_indicators[11][1].color = sf::Color::Cyan;


}
