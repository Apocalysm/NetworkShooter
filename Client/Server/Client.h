#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\IpAddress.hpp"



class Client
{
public:
	Client(sf::IpAddress adress, unsigned short port, int id);
	~Client();

	void Update();

	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	void GetSpeed();
	const sf::IpAddress GetIp() const;
	const unsigned short GetPort() const;
	void SetID(int newID);
	const int GetID() const;

private:

	sf::Vector2f m_clientPos;
	sf::IpAddress m_ip;
	int m_id;
	unsigned short m_port;
};

