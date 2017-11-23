#include <string>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

#include "KeyboardHandler.h"
#include "Player.h"

Player::Player() :
	m_player_shape(new sf::CircleShape), m_enemy_shape(new sf::CircleShape),
	m_socket(new sf::UdpSocket), m_speed(0.03), m_server_port(27015), m_pressed(false),
	m_game_over(false)
{
	m_player_shape->setRadius(16);
	m_player_shape->setOrigin(m_player_shape->getRadius(), m_player_shape->getRadius());
	m_player_shape->setFillColor(sf::Color::Blue);
	m_player_shape->setPosition(306, 306);

	m_player_position = m_player_shape->getPosition();

	m_enemy_shape->setRadius(16);
	m_enemy_shape->setOrigin(m_enemy_shape->getRadius(), m_enemy_shape->getRadius());
	m_enemy_shape->setFillColor(sf::Color::Red);
	m_enemy_shape->setPosition(612, 612);

	if (!m_font.loadFromFile("Sketch_3D.otf"))
	{

	}
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Red);
	m_text.setCharacterSize(72);
	m_text.setPosition(410, 270);
	Initialize();
}

void Player::Initialize()
{
	m_socket->bind(sf::Socket::AnyPort);
	m_socket->setBlocking(false);
	
	//std::cout << "Please enter the IP-address of the server..." << std::endl;
	//std::string ipAddress;
	//std::getline(std::cin, ipAddress);
	m_server_address = sf::IpAddress::getLocalAddress();

	sf::Packet packet;
	int command = CONNECT;
	packet << command;
	m_socket->send(packet, m_server_address, m_server_port);
}

Player::~Player()
{
}

// Update for player
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

	//Send();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(*m_player_shape);
	window.draw(*m_enemy_shape);
	for (int i = 0; i < m_bullets_vector.size(); i++)
	{
		window.draw(m_bullets_vector[i]->GetShape());
	}
	if (m_game_over == true)
		window.draw(m_text);
}

// Input from player, such as movement
void Player::Input(sf::Event& rEvent)
{
	sf::Vector2f movementVector = sf::Vector2f(0, 0);
	float radius = m_player_shape->getRadius();

	//--------------Movement input----------------//
	if (KeyboardHandler::isKeyDown(sf::Keyboard::W))
	{
		Send();
		movementVector.y -= m_speed;
	}
	if (KeyboardHandler::isKeyDown(sf::Keyboard::A))
	{
		Send();
		movementVector.x -= m_speed;
	}

	if (KeyboardHandler::isKeyDown(sf::Keyboard::S))
	{
		Send();
		movementVector.y += m_speed;
	}

	if (KeyboardHandler::isKeyDown(sf::Keyboard::D))
	{
		Send();
		movementVector.x += m_speed;
	}
	
	m_player_shape->move(movementVector);
	if (m_player_shape->getPosition().x - radius <= 0 || m_player_shape->getPosition().x + radius >= 1280 ||
		m_player_shape->getPosition().y - radius <= 0 || m_player_shape->getPosition().y + radius >= 720)
	{
		m_player_shape->move(-movementVector);
	}
	m_enemy_shape->setPosition(m_enemy_position);

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

void Player::CloseWindow()
{
	sf::Packet packet;
	int command = DISCONNECT;
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
		sf::Vector2f startPos;
		packet >> m_player_position >> m_enemy_position >> m_id;
		std::cout << m_id;
	}

	if(command == UPDATEPOS)
		packet  >> m_enemy_position.x >> m_enemy_position.y;

	if (command == NEWBULLET)
	{
		sf::Vector2f pos;
		sf::Vector2f mousepos;
		int owner_id;
		packet >> owner_id >> mousepos >> pos;
		m_bullets_vector.push_back(new Bullet(pos, mousepos, owner_id));
	}

	if (command == SERVERFULL)
		CloseWindow();

	if (command == WIN)
	{
		m_text.setString("YOU WIN!!");
		m_game_over = true;
	}
	if (command == LOSE)
	{
		m_text.setString("YOU LOSE!!");
		m_game_over = true;
	}
}

void Player::Send()
{
	sf::Packet packet;
	int command = 1;
	packet << command << m_player_position.x << m_player_position.y;
	//std::cout << player_position.x << std::endl;
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
			if (m_id != m_bullets_vector[i]->Getid())
			{
				std::cout << "Hit by bullet" << std::endl;
				sf::Packet packet;
				int command = BULLETHIT;
				packet << command << m_id;

				m_socket->send(packet, m_server_address, m_server_port);
			}
		}
	}
}

const sf::CircleShape* Player::GetShape() const
{
	return m_player_shape;
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