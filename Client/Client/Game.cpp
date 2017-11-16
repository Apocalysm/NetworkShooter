#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>

#include "Game.h"
#include "Player.h"
#include "KeyboardHandler.h"

Game::Game() :
	window(new sf::RenderWindow), player(new Player)
{
	window->create(sf::VideoMode(1280, 720), "Shooter: Multiplayer");
	KeyboardHandler::Initialize();
}

Game::~Game()
{
}

void Game::Update()
{
	sf::Event event;
	while (window->isOpen())
	{	
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				KeyboardHandler::setKeyDown(event.key.code);

				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
			}
		}

		window->clear();

		player->Update();
		KeyboardHandler::clearKeys();

		player->Draw(*window);
		window->display();
	}
}