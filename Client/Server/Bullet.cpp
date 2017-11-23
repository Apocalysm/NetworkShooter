#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir) :
	m_position(pos), m_direction(dir), m_destroy(false)
{
	std::cout << m_position.x << std::endl;
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	m_position.x += m_direction.x;
	m_position.y += m_direction.y;

	std::cout << m_position.x << std::endl;

	if (m_position.x > 1280 || m_position.x < 0 || m_position.y > 730 || m_position.y < 0)
		m_destroy = true;
}

const sf::Vector2f& Bullet::GetPos() const
{
	return m_position;
}

const bool Bullet::GetDestroy() const
{
	return m_destroy;
}
