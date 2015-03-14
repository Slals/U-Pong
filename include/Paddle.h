#ifndef PADDLE_H
#define PADDLE_H

#include "Shield.h"
#include "PaddleEffect.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Reverse.h"
#include "Dash.h"

#include <vector>

class Game;

class Paddle : public Entity
{
    public:
		Paddle(std::shared_ptr<World>& world, unsigned int const id, sf::Vector2f const& pos, std::shared_ptr<Shield>& shield);

        void upPow(float val);
        void downPow(float val);
        void render();
        void moveUp(sf::Time delta);
        void moveDown(sf::Time delta);
        void setVelocity(float value);

        float getRotation() const { return _view_paddle.getRotation(); };
        bool isAtkState() const { return _state; };
        bool isDefState() const { return !_state; };
        float getPower() const { return _power; };
        float getSpeed() const { return _speed; };
        sf::Vector2f const& getVelocity() const { return _velocity; };

        void rotate(unsigned int degree);
        void reverseState();

        void onWorldCollision();
        void onObjectCollision(std::shared_ptr<Entity>& entity);
        sf::IntRect const& getBound() const;

        void update(sf::Time delta);

    protected:
		float _power = 0.1f;
        std::vector<PaddleEffect> _effect;
        sf::Sprite _view_paddle;
        int _id;
        float _speed = 1.f;
        sf::Vector2f _velocity;
        std::vector<std::unique_ptr<Skill>> _skills;
        bool _state = true;
        std::shared_ptr<Shield> _shield;

        void initViews(unsigned int const color);

};

#endif // PADDLE_H
