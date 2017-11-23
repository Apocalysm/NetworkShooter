#pragma once
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RectangleShape;
}

class Bullet
{
public:
	Bullet(sf::Vector2f& position, sf::Vector2f& mouse_pos, int Owner_ID);
	~Bullet();

	const sf::RectangleShape& GetShape() const;
	const sf::Vector2f& GetDir() const;
	const int Getid() const;

	void Move();

private:
	float m_speed;
	int m_ownerid;

	sf::Vector2f m_dir;
	sf::RectangleShape m_bullet_shape;
};