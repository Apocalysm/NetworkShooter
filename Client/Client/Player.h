#pragma once

namespace sf
{
	class CircleShape;
	class RectangleShape;
	class Window;
	class Mouse;
	class IpAdress;
	class UdpSocket;
	class Event;
}

class Player
{
public:
	Player();
	~Player();

	void Input();
	void Update();
	sf::CircleShape* GetShape();

private:
	void Connect();
	void Disconnet();

	void Send();
	void Receive();

	sf::CircleShape* player_shape;
	sf::RectangleShape* bullet;
	sf::Mouse* mouse;
	sf::UdpSocket* socket;
	const sf::IpAdress* server_Adress;

	float speed;
	const const unsigned short server_port = 27015;
};