#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

const std::string IMG_PAD = "";
const std::string IMG_WORLD = "";
const std::string IMG_UI = "";
const std::string IMG_SHIELD = "";

class ResourceManager
{
	public:
		static ResourceManager& getInstance();

		void loadGameTexture();
		sf::Texture const& getPaddleTexture() const { return _t_paddle; };
		sf::Texture const& getWorldTexture() const { return _t_paddle; };
		sf::Texture const& getUITexture() const { return _t_UI; };
		sf::Texture const& getShieldTexture() const { return _t_shield; };

	private:
		ResourceManager& operator=(const ResourceManager&) { };
		ResourceManager (const ResourceManager&) { };

		static ResourceManager _res_instance;
		ResourceManager();
		~ResourceManager();

		sf::Texture _t_paddle;
		sf::Texture _t_world;
		sf::Texture _t_UI;
		sf::Texture _t_shield;

};

#endif // RESOURCE_H_INCLUDED
