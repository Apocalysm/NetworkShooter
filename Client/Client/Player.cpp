#include <string>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

#include "KeyboardHandler.h"
#include "Player.h"

Player::Player() :
	player_shape(new sf::CircleShape), enemy_shape(new sf::CircleShape),
	socket(new sf::UdpSocket), speed(0.03), server_port(27015), is_pressed(1)
{
	player_shape->setRadius(16);
	player_shape->setOrigin(player_shape->getRadius(), player_shape->getRadius());
	player_shape->setFillColor(sf::Color::Blue);
	//player_shape->setPosition(306, 306);

	player_position = player_shape->getPosition();

	enemy_shape->setRadius(16);
	enemy_shape->setOrigin(enemy_shape->getRadius(), enemy_shape->getRadius());
	enemy_shape->setFillColor(sf::Color::Red);
	//enemy_shape->setPosition(612, 612);

	Initialize();
}

void Player::Initialize()
{
	socket->bind(sf::Socket::AnyPort);
	socket->setBlocking(false);
	
	//std::cout << "Please enter the IP-address of the server..." << std::endl;
	//std::string ipAddress;
	//std::getline(std::cin, ipAddress);
	server_Adress = sf::IpAddress::getLocalAddress();

	sf::Packet packet;
	int command = CONNECT;
	packet << command;
	socket->send(packet, server_Adress, server_port);
}

Player::~Player()
{
}

// Update for player
void Player::Update(sf::RenderWindow& window, sf::Event& rEvent)
{
	Receive();
	Input(rEvent);

	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
	if (bullets_vector.size() > 0)
	{
		for (int i = 0; i < bullets_vector.size(); i++)
		{
			bullets_vector[i]->Move();
		}
	}

	Send();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(*player_shape);
	window.draw(*enemy_shape);
	for (int i = 0; i < bullets_vector.size(); i++)
	{
		window.draw(bullets_vector[i]->GetShape());
	}	
}

// Input from player, such as movement
void Player::Input(sf::Event& rEvent)
{
	sf::Vector2f movementVector = sf::Vector2f(0, 0);

	//--------------Movement input----------------//
	if (KeyboardHandler::isKeyDown(sf::Keyboard::W))
		movementVector.y -= speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::A))
		movementVector.x -= speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::S))
		movementVector.y += speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::D))
		movementVector.x += speed;

	player_shape->move(movementVector);
	enemy_shape->setPosition(enemy_position);

	player_position = player_shape->getPosition();
	
	//------------------Shoot input----------------//
	if (rEvent.mouseButton.button == sf::Mouse::Left)
	{
		if (rEvent.type == sf::Event::MouseButtonPressed && is_pressed == 1)
		{
			bullets_vector.push_back(new Bullet(player_position, mouse_pos));
			is_pressed = 0;
		}
		else if (rEvent.type == sf::Event::MouseButtonReleased && is_pressed == 0)
		{
			is_pressed = 1;
		}
	}
}

void Player::CloseWindow()
{
	sf::Packet packet;
	int command = DISCONNECT;
	packet << command;

	socket->send(packet, server_Adress, server_port);
}

void Player::Receive()
{
	sf::Packet packet;
	sf::IpAddress senderIP;
	unsigned short sender_port;
	int command;


	socket->receive(packet, senderIP, sender_port);
	packet >> command;

	if (command == CONNECT)
	{
		sf::Vector2f startPos;
		packet >> startPos;
		player_shape->setPosition(startPos);
	}

	if(command == UPDATEPOS)
		packet  >> enemy_position.x >> enemy_position.y;

	if (command == SERVERFULL)
		CloseWindow();
}

void Player::Send()
{
	sf::Packet packet;
	int command = 1;
	packet << command << player_position.x << player_position.y;
	//std::cout << player_position.x << std::endl;
	socket->send(packet, server_Adress, server_port);
}

void Player::CreateBullet()
{
	sf::Packet packet;
	int command = BULLETHIT;
	packet << command << bullets_vector.back()->GetDir();

	socket->send(packet, server_Adress, server_port);
}

const sf::CircleShape* Player::GetShape() const
{
	return player_shape;
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