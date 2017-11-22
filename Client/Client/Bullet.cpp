#include <SFML\Graphics.hpp>

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f& position, sf::Vector2f& mouse_pos) :
	speed(0.3)
{
	bullet_shape.setSize(sf::Vector2f(2.0, 4.0));
	bullet_shape.setFillColor(sf::Color::White);
	bullet_shape.setOrigin(bullet_shape.getSize().x / 2, bullet_shape.getSize().y / 2);
	bullet_shape.setPosition(position);

	dir = sf::Vector2f(mouse_pos - position);
	dir /= std::sqrt(dir.x * dir.x + dir.y * dir.y);
	dir *= speed;

}

Bullet::~Bullet()
{
}

const sf::RectangleShape& Bullet::GetShape() const
{
	return bullet_shape;
}

void Bullet::Move()
{
	bullet_shape.move(dir);
}
