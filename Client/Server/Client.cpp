#include "Client.h"

#include <SFML/Network/IpAddress.hpp>

Client::Client(sf::IpAddress address, unsigned short port, int health) :
	m_ip(address), m_hp(health), m_port(port)
{
	
}


Client::~Client()
{
}

void Client::SetPos(sf::Vector2f pos)
{
	m_clientPos = pos;
}

//Get the postion of the client
sf::Vector2f Client::GetPos()
{
	return m_clientPos;
}

void Client::GetSpeed()
{
}

sf::IpAddress Client::GetIp()
{
	return m_ip;
}

unsigned short Client::GetPort()
{
	return m_port;
}
