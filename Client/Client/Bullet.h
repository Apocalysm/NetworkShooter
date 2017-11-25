#pragma once
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RectangleShape;
}

class Bullet
{
public:
	Bullet(sf::Vector2f& position, sf::Vector2f& mouse_pos, int owner_id);
	~Bullet();

	void Move();

	const sf::RectangleShape& GetShape() const;
	const sf::Vector2f& GetDir() const;
	const int GetId() const;
	const bool GetDestroy() const;

	void SetDestroy(bool status);

private:
	float m_speed;
	int m_owner;
	bool m_destroy;

	sf::Vector2f m_dir;
	sf::RectangleShape m_bullet_shape;
};