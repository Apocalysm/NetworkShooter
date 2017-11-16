#include "Client.h"

#include <SFML/Network/IpAddress.hpp>

Client::Client(sf::IpAddress* address, unsigned short port) : 
	ip(new sf::IpAddress)
{
	
}


Client::~Client()
{
}

void Client::SetPos(sf::Vector2f pos)
{
	clientPos = pos;
}

//Get the postion of the client
sf::Vector2f Client::GetPos()
{
	return clientPos;
}

void Client::GetSpeed()
{
}

sf::IpAddress * Client::GetIp()
{
	return ip;
}
