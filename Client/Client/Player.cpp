#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

#include "KeyboardHandler.h"
#include "Player.h"

Player::Player() :
	player_shape(new sf::CircleShape), mouse(new sf::Mouse), 
	socket(new sf::UdpSocket), speed(0.03)
{
	player_shape->setRadius(16);
	player_shape->setOrigin(player_shape->getRadius(), player_shape->getRadius());
	player_shape->setFillColor(sf::Color::Red);
	player_shape->setPosition(306, 306);

	socket->bind(sf::Socket::AnyPort);
}

Player::~Player()
{
}

// Update for player
void Player::Update()
{
	Input();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(*player_shape);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bullets_vector.push_back(new Bullet(player_shape->getPosition()));
		// direction = muspekarens position minus bullets position och normalisera det
		//bullet->get
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

void Player::Send()
{
	
}

void Player::Receive()
{
}
