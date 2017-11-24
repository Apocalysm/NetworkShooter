#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\IpAddress.hpp"

class Client
{
public:
	Client(sf::IpAddress adress, unsigned short port, int id);
	~Client();


	const sf::Vector2f& GetPos() const;
	const int GetID() const;
	const sf::IpAddress& GetIp() const;
	const unsigned short GetPort() const;
	const bool GetReady() const;

	void SetPos(sf::Vector2f pos);
	void SetID(int newID);
	void SetReady(bool ready);
private:
	sf::Vector2f m_clientPos;
	sf::IpAddress m_ip;

	bool m_ready;
	int m_id;
	unsigned short m_port;
};

