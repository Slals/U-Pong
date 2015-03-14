#include "ResourceManager.h"

ResourceManager ResourceManager::_res_instance = ResourceManager();

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager& ResourceManager::getInstance()
{
	return _res_instance;
}

void ResourceManager::loadGameTexture()
{
	if(!_t_paddle.loadFromFile(IMG_PAD))
		std::cout << "Error : can't find PAD texture " << std::endl;

    if(!_t_world.loadFromFile(IMG_WORLD))
        std::cout << "Error : can't find WORLD texture " << std::endl;

	if(!_t_UI.loadFromFile(IMG_UI))
		std::cout << "Error : can't find UI texture " << std::endl;

	if(!_t_shield.loadFromFile(IMG_SHIELD))
		std::cout << "Error : can't find Shield texture " << std::endl;
}

