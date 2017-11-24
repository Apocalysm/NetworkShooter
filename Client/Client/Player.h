#pragma once
#include <vector>

#include "SFML\Network\IpAddress.hpp"
#include "SFML\Network\Packet.hpp"

#include "Bullet.h"

enum COMMAND {
	CONNECT = 0,
	UPDATEPOS = 1,
	DISCONNECT = 2,
	NEWBULLET = 3,
	SERVERFULL = 4,
	BULLETPOS = 5,
	BULLETHIT = 6,
	WIN = 7,
	LOSE = 8,
	READY = 9,
	WAITING = 10,
	START = 11
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
		
	void Update(sf::RenderWindow& window, sf::Event& sf_event);
	void Draw(sf::RenderWindow& window);

	void Input(sf::Event& sf_event);

	const sf::CircleShape* GetShape() const;

	void CloseWindow();

private:
	void Initialize();
	void Receive();
	void Send();
	void CreateBullet();
	void CheckBulletCollision();

	std::vector<Bullet*> m_bullets_vector;

	sf::CircleShape* m_player_shape;
	sf::CircleShape* m_enemy_shape;
	sf::Vector2f m_mouse_position; 
	sf::UdpSocket* m_socket;
	sf::IpAddress m_server_address;
	sf::Vector2f m_player_position;
	sf::Vector2f m_enemy_position;
	sf::Text m_text;
	sf::Font m_font;

	float m_speed;
	unsigned short m_server_port;
	int m_id;
	bool m_pressed;
	bool m_key_pressed;
	bool m_ready;
	bool m_game_running;
	bool m_game_over;
	bool m_dead;
	bool m_won;
};

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);