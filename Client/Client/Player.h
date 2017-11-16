#pragma once
#include <vector>
#include "Bullet.h"

namespace sf
{
	class CircleShape;
	class RectangleShape;
	class Window;
	class Renderwindow;
	class Mouse;
	class IpAdress;
	class UdpSocket;
	class Event;
}
class bullet;

class Player
{
public:
	Player();
	~Player();
		
	void Update();
	void Draw(sf::RenderWindow& window);

	void Input();
	const sf::CircleShape* GetShape() const;

private:
	void Connect();
	void Disconnet();

	void Send();
	void Receive();

	std::vector<Bullet*> bullets_vector;

	sf::CircleShape* player_shape;
	sf::Mouse* mouse;
	sf::UdpSocket* socket;
	const sf::IpAdress* server_Adress;

	float speed;
	const unsigned short server_port = 27015;
};