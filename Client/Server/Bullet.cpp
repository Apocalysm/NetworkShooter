#include "Bullet.h"


Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir) :
	position(pos), direction(dir)
{

}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	position.x += direction.x;
	position.y += direction.y;
}
