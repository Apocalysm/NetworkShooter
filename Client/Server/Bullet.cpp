#include "Bullet.h"


Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir) :
	position(pos), direction(dir), destroy(false)
{

}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	position.x += direction.x;
	position.y += direction.y;

	if (position.x > 1280 || position.x < 0 || position.y > 730 || position.y < 0)
		destroy = true;
}

sf::Vector2f Bullet::GetPos()
{
	return position;
}

bool Bullet::GetDestroy()
{
	return destroy;
}
