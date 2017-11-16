#include "Game.h"
#include "Player.h"
#include <SFML\Graphics.hpp>

Game::Game() :
	window(new sf::RenderWindow), player(new Player)
{
	window->create(sf::VideoMode(1280, 720), "Air Hockey Wooh!");
}

Game::~Game()
{
}

void Game::Update()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		player->Update();

		window->draw(*player->GetShape());
		window->display();
	}
}