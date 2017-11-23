#include <SFML\Graphics.hpp>

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f& position, sf::Vector2f& mouse_pos, int owner_id) :
	m_speed(0.3), m_ownerid(owner_id), m_destroy(false)
{
	m_bullet_shape.setSize(sf::Vector2f(2.0, 4.0));
	m_bullet_shape.setFillColor(sf::Color::White);
	m_bullet_shape.setOrigin(m_bullet_shape.getSize().x / 2, m_bullet_shape.getSize().y / 2);
	m_bullet_shape.setPosition(position);

	m_dir = sf::Vector2f(mouse_pos - position);
	m_dir /= std::sqrt(m_dir.x * m_dir.x + m_dir.y * m_dir.y);
	m_dir *= m_speed;

}

Bullet::~Bullet()
{

}

const sf::RectangleShape& Bullet::GetShape() const
{
	return m_bullet_shape;
}

const sf::Vector2f & Bullet::GetDir() const
{
	return m_dir;
}

const int Bullet::Getid() const
{
	return m_ownerid;
}

const bool Bullet::GetDestroy()
{
	return m_destroy;
}

void Bullet::SetDestroy(bool des)
{
	m_destroy = des;
}

void Bullet::Move()
{
	m_bullet_shape.move(m_dir);
}
