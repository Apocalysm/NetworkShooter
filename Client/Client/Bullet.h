#pragma once
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RectangleShape;
}

class Bullet
{
public:
	Bullet(sf::Vector2f& position, sf::Vector2f& mouse_pos);
	~Bullet();

	const sf::RectangleShape& GetShape() const;
	const sf::Vector2f& GetDir() const;
	void Move();

private:
	float m_speed;

	sf::Vector2f m_dir;
	sf::RectangleShape m_bullet_shape;
};