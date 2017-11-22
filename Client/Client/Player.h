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
	class UdpSocket;
}

class Player
{
public:
	Player();
	~Player();
		
	void Update(sf::RenderWindow& window, sf::Event& rEvent);
	void Draw(sf::RenderWindow& window);

	void Input(sf::Event& rEvent);
	const sf::CircleShape* GetShape() const;

private:
	void Connect();
	void Disconnet();

	void Initialize();
	void Receive();
	void Send();

	std::vector<Bullet*> bullets_vector;

	sf::CircleShape* player_shape;
	sf::CircleShape* enemy_shape;
	sf::Vector2f mouse_pos; 
	sf::UdpSocket* socket;
	sf::IpAddress server_Adress;

	sf::Vector2f player_position;
	sf::Vector2f enemy_position;
	float speed;
	int is_pressed;
	unsigned short server_port;
};

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);