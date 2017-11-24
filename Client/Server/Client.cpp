#include "Client.h"

#include <SFML/Network/IpAddress.hpp>

Client::Client(sf::IpAddress address, unsigned short port, int health) :
	m_ip(address), m_id(health), m_port(port), m_ready(false)
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
const sf::Vector2f& Client::GetPos() const
{
	return m_clientPos;
}


const sf::IpAddress& Client::GetIp() const
{
	return m_ip;
}

const unsigned short Client::GetPort() const
{
	return m_port;
}

const bool Client::GetReady() const
{
	return m_ready;
}

void Client::SetID(int newID)
{
	m_id = newID;
}

void Client::SetReady(bool ready)
{
	m_ready = ready;
}

const int Client::GetID() const
{
	return m_id;
}
