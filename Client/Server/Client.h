#pragma once
#include "SFML\System\Vector2.hpp"

namespace sf
{
	class IpAddress;
}

class Client
{
public:
	Client(sf::IpAddress* adress, unsigned short port);
	~Client();

	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	void GetSpeed();
	sf::IpAddress* GetIp();
private:

	sf::Vector2f clientPos;
	sf::IpAddress* ip;
};

