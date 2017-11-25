#pragma once
#include "SFML\System\Vector2.hpp"


class Bullet
{
public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir);
	~Bullet();

	void Update();

	const sf::Vector2f& GetPos() const;
	const bool GetDestroy() const;

private:
	bool m_destroy;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;
};