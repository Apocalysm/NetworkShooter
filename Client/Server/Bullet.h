#pragma once
#include "SFML\System\Vector2.hpp"


class Bullet
{
public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir);
	~Bullet();

	void Update();
private:
	sf::Vector2f position;
	sf::Vector2f direction;

};