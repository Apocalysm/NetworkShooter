#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\IpAddress.hpp"



class Client
{
public:
	Client(sf::IpAddress adress, unsigned short port, int health);
	~Client();

	void Update();

	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	void GetSpeed();
	sf::IpAddress GetIp();
	unsigned short GetPort();

private:

	sf::Vector2f m_clientPos;
	sf::IpAddress m_ip;
	int m_hp;
	unsigned short m_port;
};

