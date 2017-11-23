#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>

#include "Game.h"
#include "Player.h"
#include "KeyboardHandler.h"

Game::Game() :
	m_window(new sf::RenderWindow), m_player(new Player)
{
	m_window->create(sf::VideoMode(1280, 720), "Shooter: Multiplayer", sf::Style::Titlebar | sf::Style::Close);
	KeyboardHandler::Initialize();
}

Game::~Game()
{
}

void Game::Update()
{
	sf::Event event;
	while (m_window->isOpen())
	{	
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_player->CloseWindow();
				m_window->close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				KeyboardHandler::setKeyDown(event.key.code);
			}
		}

		m_window->clear();

		m_player->Update(*m_window, event);
		KeyboardHandler::clearKeys();

		m_player->Draw(*m_window);
		m_window->display();
	}
}