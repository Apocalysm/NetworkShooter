#pragma once
#include <vector>

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"

#include "Bullet.h"

namespace sf
{
	class CircleShape;
	class RectangleShape;
	class Window;
	class RenderWindow;
	class Mouse;
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

	sf::Vector2f vector;

private:
	void Connect();
	void Disconnet();

	void Initialize();
	void Receive();
	void Send();

	std::vector<Bullet*> bullets_vector;

	sf::CircleShape* player_shape;
	sf::CircleShape* enemy_shape;
	sf::Mouse* mouse;
	sf::Event player_event;
	sf::UdpSocket* socket;
	sf::IpAddress server_Adress;

	sf::Vector2f player_position;
	sf::Vector2f enemy_position;
	float speed;
	int is_pressed = 0;
	unsigned short server_port;
};

sf::Packet& operator <<(sf::Packet& packet, const Player& player);
sf::Packet& operator >>(sf::Packet& packet, Player& player);