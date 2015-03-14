#include "Game.h"

std::shared_ptr<Screen> Game::SCREEN = std::make_shared<GameScreen>();
Game Game::_game_instance = Game();
Game::Game():
	_window(sf::VideoMode(800, 600, 32), "Ultimate Pong")
{
	_window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
}

Game::~Game()
{
	//dtor
}

Game& Game::getInstance()
{
    return _game_instance;
}

void Game::changeWinSize(unsigned int width, unsigned int height)
{
    _window.create(sf::VideoMode(width, height, 32), "Ultimate Pong");
    _window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
}

void Game::render()
{
	_window.clear();
	Game::SCREEN->render();
	_window.display();
}

void Game::handleInput()
{
	sf::Event e;
	while(_window.pollEvent(e))
	{
		switch(e.type)
		{
			case sf::Event::Closed:
				_window.close();
				break;

            case sf::Event::KeyPressed:
                if(e.key.code == sf::Keyboard::F1)
                    changeWinSize(800, 600);
                else if(e.key.code == sf::Keyboard::F2)
                    changeWinSize(1024, 768);
				else if(e.key.code == sf::Keyboard::F3)
					changeWinSize(1920, 1080);
				else if(e.key.code == sf::Keyboard::F4)
				{
					_window.create(sf::VideoMode(1920, 1080, 32), "Ultimate Pong", sf::Style::Fullscreen);
					_window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
				}
				else if(e.key.code == sf::Keyboard::Escape)
					_window.close();
				break;
		}
	}

	Game::SCREEN->handleInput();
}

void Game::run()
{
	sf::Clock clock;

	_window.setKeyRepeatEnabled(false);

    while(_window.isOpen())
    {
		sf::Time delta = clock.restart();
		handleInput();
		Game::SCREEN->update(delta);

        render();
    }
}
