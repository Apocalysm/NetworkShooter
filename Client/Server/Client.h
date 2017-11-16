#pragma once
namespace sf
{
	class IpAdress;
}

class Client
{
public:
	Client(sf::IpAdress* adress, unsigned short port);
	~Client();
};

