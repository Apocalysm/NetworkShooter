#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\IpAddress.hpp"

class Client
{
public:
	Client(sf::IpAddress adress, unsigned short port, int id);
	~Client();

	void Update();

	const sf::Vector2f& GetPos() const;
	const int GetID() const;
	void GetSpeed(); // void GetSpeed? really?
	const sf::IpAddress& GetIp() const;
	const unsigned short GetPort() const;

	void SetPos(sf::Vector2f pos);
	void SetID(int newID);

private:
	sf::Vector2f m_clientPos;
	sf::IpAddress m_ip;

	int m_id;
	unsigned short m_port;
};

