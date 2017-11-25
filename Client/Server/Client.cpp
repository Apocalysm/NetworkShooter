#include <SFML/Network/IpAddress.hpp>

#include "Client.h"

Client::Client(sf::IpAddress address, unsigned short port, int id) :
	m_ip(address), m_id(id), m_port(port), m_ready(false)
{
	
}


Client::~Client()
{

}


const sf::Vector2f& Client::GetPos() const
{
	return m_client_pos;
}


const int Client::GetId() const
{
	return m_id;
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


void Client::SetPos(sf::Vector2f position)
{
	m_client_pos = position;
}


void Client::SetId(int new_id)
{
	m_id = new_id;
}


void Client::SetReady(bool state)
{
	m_ready = state;
}
