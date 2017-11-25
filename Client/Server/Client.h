#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\IpAddress.hpp"

class Client
{
public:
	Client(sf::IpAddress address, unsigned short port, int id);
	~Client();

	const sf::Vector2f& GetPos() const;
	const int GetId() const;
	const sf::IpAddress& GetIp() const;
	const unsigned short GetPort() const;
	const bool GetReady() const;

	void SetPos(sf::Vector2f position);
	void SetId(int new_id);
	void SetReady(bool state);

private:
	sf::Vector2f m_client_pos;
	sf::IpAddress m_ip;

	bool m_ready;
	int m_id;
	unsigned short m_port;
};
