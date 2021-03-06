#include <string>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

#include "KeyboardHandler.h"
#include "Numeric.h"
#include "Player.h"

Player::Player() :
	m_player_shape(new sf::CircleShape), m_enemy_shape(new sf::CircleShape),
	m_socket(new sf::UdpSocket), m_speed(0.1), m_server_port(27015), m_pressed(false),
	m_game_over(true), m_dead(false), m_won(false), m_game_running(false), m_ready(false),
	m_key_pressed(false)
{
	m_player_shape->setRadius(16);
	m_player_shape->setOrigin(m_player_shape->getRadius(), m_player_shape->getRadius());
	m_player_shape->setFillColor(sf::Color::Blue);

	m_enemy_shape->setRadius(16);
	m_enemy_shape->setOrigin(m_enemy_shape->getRadius(), m_enemy_shape->getRadius());
	m_enemy_shape->setFillColor(sf::Color::Red);

	if (!m_font.loadFromFile("Sketch_3D.otf")){}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Red);
	m_text.setCharacterSize(72);
	m_text.setString("Press R for ready");
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(640, 360);
	
	Initialize();
}


Player::~Player()
{
}


void Player::Update(sf::RenderWindow& window, sf::Event& rEvent)
{
	Receive();
	Input(rEvent);

	m_mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
	if (m_bullets_vector.size() > 0)
	{
		for (int i = 0; i < m_bullets_vector.size(); i++)
		{
			m_bullets_vector[i]->Move();
		}
		CheckBulletCollision();
	}

	for (auto it = m_bullets_vector.begin(); it != m_bullets_vector.end();)
	{
		if ((*it)->GetShape().getPosition().x < 0 || (*it)->GetShape().getPosition().x > 1280 ||
			(*it)->GetShape().getPosition().y < 0 || (*it)->GetShape().getPosition().y > 720)
		{
			(*it)->SetDestroy(true);
		}

		// Delete the bullet if it's state is destroy
		if ((*it)->GetDestroy() == true)
		{
			delete(*it);
			it = m_bullets_vector.erase(it);
			continue;
		}
		it++;
	}
}


void Player::Draw(sf::RenderWindow& window)
{
	if (m_dead != true)
		window.draw(*m_player_shape);
	if (!m_won)
		window.draw(*m_enemy_shape);
	for (int i = 0; i < m_bullets_vector.size(); i++)
	{
		window.draw(m_bullets_vector[i]->GetShape());
	}
	if (m_game_over == true)
		window.draw(m_text);
}


// Input from player
void Player::Input(sf::Event& rEvent)
{
	// If player isn't ready and presses R, then inform server that client is ready
	if (KeyboardHandler::isKeyDown(sf::Keyboard::R) && m_key_pressed == false)
	{
		sf::Packet packet;
		int command = READY;
		packet << command << m_id;
		m_socket->send(packet, m_server_address, m_server_port);

		m_key_pressed = true;
	}

	sf::Vector2f movementVector = sf::Vector2f(0, 0);
	float radius = m_player_shape->getRadius();
	if (!m_dead && !m_game_over)
	{
		//--------------Movement input----------------//
		if (KeyboardHandler::isKeyDown(sf::Keyboard::W))
		{
			SendPosition();
			movementVector.y -= m_speed;
		}
		if (KeyboardHandler::isKeyDown(sf::Keyboard::A))
		{
			SendPosition();
			movementVector.x -= m_speed;
		}

		if (KeyboardHandler::isKeyDown(sf::Keyboard::S))
		{
			SendPosition();
			movementVector.y += m_speed;
		}

		if (KeyboardHandler::isKeyDown(sf::Keyboard::D))
		{
			SendPosition();
			movementVector.x += m_speed;
		}

		m_player_shape->move(movementVector);
		if (m_player_shape->getPosition().x - radius <= 0 || m_player_shape->getPosition().x + radius >= 1280 ||
			m_player_shape->getPosition().y - radius <= 0 || m_player_shape->getPosition().y + radius >= 720)
		{
			m_player_shape->move(-movementVector);
		}

		m_player_position = m_player_shape->getPosition();

		//------------------Shoot input----------------//
		if (rEvent.mouseButton.button == sf::Mouse::Left)
		{
			if (rEvent.type == sf::Event::MouseButtonPressed && m_pressed == false)
			{
				m_pressed = true;
				CreateBullet();
			}
			else if (rEvent.type == sf::Event::MouseButtonReleased && m_pressed == true)
			{
				m_pressed = false;
			}
		}
	}

	m_enemy_shape->setPosition(m_enemy_position);
}

// Tells the server that the client has disconnected before exiting the application
void Player::CloseWindow()
{
	sf::Packet packet;
	int command = DISCONNECT;
	packet << command;

	m_socket->send(packet, m_server_address, m_server_port);
}


const sf::CircleShape* Player::GetShape() const
{
	return m_player_shape;
}


void Player::Initialize()
{
	m_socket->bind(sf::Socket::AnyPort);
	m_socket->setBlocking(false);

	std::cout << "Please enter the ip-address of the server..." << std::endl;
	std::string ip_address;
	while (true)
	{
		std::getline(std::cin, ip_address);
		if (Numeric::IsDigit(ip_address.c_str(), sizeof(ip_address)) == true)
			break;
		std::cout << "Invalid character" << std::endl;
	}
	m_server_address = ip_address;

	sf::Packet packet;
	int command = CONNECT;
	packet << command;

	m_socket->send(packet, m_server_address, m_server_port);
}


void Player::Receive()
{
	sf::Packet packet;
	sf::IpAddress senderIP;
	unsigned short sender_port;
	int command;

	m_socket->receive(packet, senderIP, sender_port);
	packet >> command;

	if (command == CONNECT)
	{
		packet >> m_player_position >> m_enemy_position >> m_id;
		m_player_shape->setPosition(m_player_position);
		m_enemy_shape->setPosition(m_enemy_position);
		std::cout << m_id;
	}

	if(command == UPDATEPOS)
		packet  >> m_enemy_position.x >> m_enemy_position.y;

	if (command == NEWBULLET)
	{
		sf::Vector2f pos;
		sf::Vector2f mouse_pos;
		int owner_id;
		packet >> owner_id >> mouse_pos >> pos;
		m_bullets_vector.push_back(new Bullet(pos, mouse_pos, owner_id));
	}

	if (command == SERVERFULL)
		CloseWindow();

	if (command == WIN)
	{
		m_text.setString("YOU WON!!");
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
		m_text.setPosition(640, 360);
		m_game_over = true;
		m_won = true;
		for (size_t i = 0; i < m_bullets_vector.size(); i++)
		{
			if (m_bullets_vector[i]->GetId() != m_id)
				m_bullets_vector[i]->SetDestroy(true);
		}
	}

	if (command == LOSE)
	{
		m_text.setString("YOU LOST!!");
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
		m_text.setPosition(640, 360);
		m_game_over = true;
		m_dead = true;
		for (size_t i = 0; i < m_bullets_vector.size(); i++)
		{
			if (m_bullets_vector[i]->GetId() == m_id)
				m_bullets_vector[i]->SetDestroy(true);
		}
	}

	if (command == WAITING)
	{
		m_text.setString("Waiting for players...");
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
		m_text.setPosition(640, 360);
		m_game_over = true;
	}

	if (command == START)
	{
		packet >> m_ready;
		m_game_over = false;
		m_game_running = true;
	}
}


void Player::SendPosition()
{
	sf::Packet packet;
	int command = 1;
	packet << command << m_player_position.x << m_player_position.y;
	m_socket->send(packet, m_server_address, m_server_port);
}


void Player::CreateBullet()
{
	sf::Packet packet;
	int command = NEWBULLET;
	packet << command << m_id << m_mouse_position << m_player_shape->getPosition() ;

	m_socket->send(packet, m_server_address, m_server_port);
}


void Player::CheckBulletCollision()
{
	for (int i = 0; i < m_bullets_vector.size(); i++)
	{
		if (m_player_shape->getGlobalBounds().contains(m_bullets_vector[i]->GetShape().getPosition()))
		{
			if (m_id != m_bullets_vector[i]->GetId())
			{
				sf::Packet packet;
				int command = BULLETHIT;
				packet << command << m_id;

				m_socket->send(packet, m_server_address, m_server_port);

				m_bullets_vector[i]->SetDestroy(true);
			}
		}
	}
}


//Overload for paket with an vector2f
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v)
{
	return packet << v.x << v.y;
}


sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v)
{
	return packet >> v.x >> v.y;
}