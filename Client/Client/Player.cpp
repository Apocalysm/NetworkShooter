#include <string>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

#include "KeyboardHandler.h"
#include "Player.h"

Player::Player() :
	player_shape(new sf::CircleShape), enemy_shape(new sf::CircleShape), mouse(new sf::Mouse),
	socket(new sf::UdpSocket), speed(0.03), server_port(27015)
{
	player_shape->setRadius(16);
	player_shape->setOrigin(player_shape->getRadius(), player_shape->getRadius());
	player_shape->setFillColor(sf::Color::Blue);
	player_shape->setPosition(306, 306);

	player_position = player_shape->getPosition();

	enemy_shape->setRadius(16);
	enemy_shape->setOrigin(enemy_shape->getRadius(), enemy_shape->getRadius());
	enemy_shape->setFillColor(sf::Color::Red);
	enemy_shape->setPosition(612, 612);

	Initialize();
}

void Player::Initialize()
{
	socket->bind(sf::Socket::AnyPort);
	socket->setBlocking(false);
	std::cout << "Please enter the IP-address of the server..." << std::endl;

	std::string ipAddress;
	std::getline(std::cin, ipAddress);
	server_Adress = ipAddress;

	sf::Packet packet;
	std::string command = "Connect";
	packet << command;
	socket->send(packet, server_Adress, server_port);
}

Player::~Player()
{
}

// Update for player
void Player::Update()
{
	Receive();
	Input();
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
void Player::Input()
{
	sf::Vector2f player_pos = player_shape->getPosition();
	sf::Vector2f movementVector = sf::Vector2f(0, 0);

	//--------------Movement input------------------.
	if (KeyboardHandler::isKeyDown(sf::Keyboard::W))
		movementVector.y -= speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::A))
		movementVector.x -= speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::S))
		movementVector.y += speed;

	if (KeyboardHandler::isKeyDown(sf::Keyboard::D))
		movementVector.x += speed;

	player_shape->move(movementVector);

	// Shoot input
	if (player_event.mouseButton.button == sf::Mouse::Left)
	{
		if (player_event.type == sf::Event::MouseButtonPressed)
		{
			is_pressed = 0;
		}
		else if (player_event.type == sf::Event::MouseButtonReleased && is_pressed == 0)
		{
			bullets_vector.push_back(new Bullet(player_shape->getPosition()));
			// direction = muspekarens position minus bullets position och normalisera det
			//bullet->get
			is_pressed++;
		}
	}
}

const sf::CircleShape* Player::GetShape() const
{
	return player_shape;
}

void Player::Connect()
{
}

void Player::Disconnet()
{
}

void Player::Receive()
{
	sf::Packet packet;
	sf::IpAddress senderIP;
	float enemy_positionx;
	float enemy_positiony;
	unsigned short sender_port;

	socket->receive(packet, senderIP, sender_port);
	packet >> enemy_positionx >> enemy_positiony;

	//enemy_position = sf::Vector2f(enemy_positionx, enemy_positiony);

	enemy_shape->setPosition(enemy_positionx, enemy_positiony);
}

void Player::Send()
{
	sf::Packet packet;
	packet << player_position.x << player_position.y;
	socket->send(packet, server_Adress, server_port);
}