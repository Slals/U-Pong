#include "UI.h"
#include "Game.h"

UI::UI()
{
	sf::IntRect txt(0, 0, 1920, 125);
    _view_UI1.setTexture(ResourceManager::getInstance().getUITexture());
    _view_UI1.setTextureRect(txt);
    _view_UI1.setColor(sf::Color::Blue);
    _view_UI1.setPosition(0, 0);

    _view_UI2.setTexture(ResourceManager::getInstance().getUITexture());
    _view_UI2.setTextureRect(txt);
    _view_UI2.setColor(sf::Color::Blue);
    _view_UI2.setPosition(0, 955);
}

void UI::update()
{

}

void UI::render()
{
	Game::getInstance().getWindow().draw(_view_UI1);
	Game::getInstance().getWindow().draw(_view_UI2);
}
