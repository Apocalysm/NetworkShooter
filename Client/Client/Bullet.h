#pragma once
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RectangleShape;
}

class Bullet
{
public:
	Bullet(sf::Vector2f position);
	~Bullet();

	const sf::RectangleShape& GetShape() const;

private:
	float speed;

	sf::RectangleShape bullet_shape;
};