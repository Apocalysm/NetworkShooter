#pragma once
#include <vector>

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"

#include "Bullet.h"

enum COMMAND { 
	CONNECT = 0,
	UPDATEPOS = 1,
	DISCONNECT = 2,
	BULLETHIT = 3,
	SERVERFULL = 4,
	BULLETPOS = 5
};

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
	void CloseWindow();

	const sf::CircleShape* GetShape() const;

private:
	void Initialize();
	void Receive();
	void Send();

	void CreateBullet();

	std::vector<Bullet*> m_bullets_vector;

	sf::CircleShape* m_player_shape;
	sf::CircleShape* m_enemy_shape;
	sf::Vector2f m_mouse_position; 
	sf::UdpSocket* m_socket;
	sf::IpAddress m_server_address;
	sf::Vector2f m_player_position;
	sf::Vector2f m_enemy_position;

	float m_speed;
	int m_pressed;
	unsigned short m_server_port;
};

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);