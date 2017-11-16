#include "Player.h"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"

Player::Player() :
	player_shape(new sf::CircleShape), mouse(new sf::Mouse), 
	socket(new sf::UdpSocket), speed(0.03)
{
	player_shape->setRadius(16);
	player_shape->setOrigin(player_shape->getRadius(), player_shape->getRadius());
	player_shape->setFillColor(sf::Color::Red);
	player_shape->setPosition(306, 306);

	bullet = new sf::RectangleShape;
	bullet->setSize(sf::Vector2f(2, 4));
	bullet->setOrigin(bullet->getSize().x / 2, bullet->getSize().y / 2);

	socket->bind(sf::Socket::AnyPort);
}

Player::~Player()
{
}

//Update for player
void Player::Update()
{
	Input();
}

//Input from player, such as movement
void Player::Input()
{
	sf::Vector2f player_pos = player_shape->getPosition();

	//--------------Movement input------------------.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player_pos.y -= speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player_pos.x -= speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player_pos.y += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player_pos.x += speed;
	player_shape->setPosition(player_pos);

	//Shoot input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bullet->setPosition(player_pos);
		//bullet->get
	}
}

sf::CircleShape* Player::GetShape()
{
	return player_shape;
}

void Player::Connect()
{
}

void Player::Disconnet()
{
}

void Player::Send()
{
	
}

void Player::Receive()
{
}
