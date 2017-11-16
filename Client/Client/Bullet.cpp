#include <SFML\Graphics.hpp>

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position) :
	speed(0)
{
	bullet_shape.setSize(sf::Vector2f(2.0, 4.0));
	bullet_shape.setFillColor(sf::Color::White);
	bullet_shape.setOrigin(bullet_shape.getSize().x / 2, bullet_shape.getSize().y / 2);
	bullet_shape.setPosition(position);
}

Bullet::~Bullet()
{
}

const sf::RectangleShape& Bullet::GetShape() const
{
	return bullet_shape;
}
