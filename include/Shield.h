#ifndef SHIELD_H
#define SHIELD_H

#include "Entity.h"
#include "ResourceManager.h"

class Game;

class Shield : public Entity
{
    public:
        Shield(sf::Vector2f const& pos);

        int getCharge() const { return _charge; };

        void render();
		void update(sf::Time delta);
		void onWorldCollision();
		void onObjectCollision(std::shared_ptr<Entity>& entity);
        sf::IntRect const& getBound() const;

        void upCharge(unsigned int value);
        void downCharge(unsigned int value);

    private:
		int _charge = 100;
		sf::Sprite _view_shield;
};

#endif // SHIELD_H
