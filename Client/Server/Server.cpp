#include <string>
#include <iostream>

#include "SFML\Network\UdpSocket.hpp"

#include "Bullet.h"
#include "Server.h"
#include "Client.h"

Server::Server() : 
	m_clientReady(0), m_socket(new sf::UdpSocket) 
{
	// Inserts functions into a function std::map
	functions_map.insert(CommandPair(CONNECT, std::bind(&Server::Connect, this, std::placeholders::_1, std::placeholders::_2)));
	functions_map.insert(CommandPair(UPDATEPOS, std::bind(&Server::UpdateClientsPos, this, std::placeholders::_1, std::placeholders::_2)));
	functions_map.insert(CommandPair(DISCONNECT, std::bind(&Server::Disconnect, this, std::placeholders::_1, std::placeholders::_2)));
	functions_map.insert(CommandPair(NEWBULLET, std::bind(&Server::CreateBullet, this, std::placeholders::_1, std::placeholders::_2)));
	functions_map.insert(CommandPair(END, std::bind(&Server::GameEnd, this, std::placeholders::_1, std::placeholders::_2)));
	functions_map.insert(CommandPair(READY, std::bind(&Server::Ready, this, std::placeholders::_1, std::placeholders::_2)));
	
	InitServer();
}


Server::~Server()
{
	delete m_socket;

	//Delete all bullets from the vector.
	for (auto it = m_bullets_vector.begin(); it != m_bullets_vector.end();)
	{
		delete(*it);
		m_bullets_vector.erase(it);
		it++;
	}

	//Delete all clients from the vector.
	for (auto it = m_clients_vector.begin(); it != m_clients_vector.end();)
	{
		delete(*it);
		m_clients_vector.erase(it);
		it++;
	}
}


//Update the server
void Server::Update()
{
	while (true)
	{
		for (auto it = m_bullets_vector.begin(); it != m_bullets_vector.end();)
		{
			//Delete the bullet if its outeside the game.
			if ((*it)->GetDestroy() == true)
			{
				delete(*it);
				it = m_bullets_vector.erase(it);
				continue;
			}
			it++;
		}

		//Update every bullet position
		for (size_t i = 0; i < m_bullets_vector.size(); i++)
		{
			m_bullets_vector[i]->Update();
		}
		
		Receive();
	}
}


void Server::InitServer()
{
	m_socket = new sf::UdpSocket();
	m_socket->bind(27015);
}


// This runs when a client is trying to connect to the server
void Server::Connect(sf::Packet pac, ClientInfo info)
{
	sf::Packet packet;

	// Checks if 2 clients are already connected
	if (m_clients_vector.size() >= 2)
	{
		packet << SERVERFULL << "The server is full!";

		m_socket->send(packet, info.address, info.port);
		return;
	}

	int id;
	sf::Vector2f Player1 = sf::Vector2f(150, 360);
	sf::Vector2f Player2 = sf::Vector2f(1130, 360);

	// Checks if no clients have connected to the server
	if (m_clients_vector.size() < 1)
	{
		// Adds player one to the game
		id = 1;
		m_clients_vector.push_back(new Client(info.address, info.port, id));
		packet << CONNECT << Player1 << Player2 << id;
		m_socket->send(packet, info.address, info.port);
		return;
	}

	// Adds player two to the game
	id = 2;
	m_clients_vector.push_back(new Client(info.address, info.port, id));	
	packet << CONNECT << Player2 << Player1 << id;
	m_socket->send(packet, info.address, info.port);
}


// This runs when a client is trying to disconnect from the server
void Server::Disconnect(sf::Packet pac, ClientInfo info)
{
	for (auto it = m_clients_vector.begin(); it != m_clients_vector.end();)
	{
		//Check if we have the right client
		if ((*it)->GetIp() == info.address && (*it)->GetPort() == info.port)
		{
			//Delete the client from the vector
			delete (*it);
			m_clients_vector.erase(it);
			break;
		}
		it++;
	}
}


// Receive from the clients
void Server::Receive()
{
	sf::Packet packet;
	ClientInfo info;

	int command = 0;

	//Getting the data from the Client
	m_socket->receive(packet, info.address, info.port);
	//Getting which command
	packet >> command;
	COMMAND cd = static_cast<COMMAND>(command);

	//Calls the function
	functions_map[cd](packet, info);
}


void Server::CreateBullet(sf::Packet pac, ClientInfo info)
{
	sf::Vector2f mousepos;
	sf::Vector2f pos;
	pac >> info.id >> mousepos >> pos;
	m_bullets_vector.push_back(new Bullet(pos, mousepos));

	pac << NEWBULLET << info.id << mousepos << pos ;
	//Send the position and the mouse position to the client.
	for (size_t i = 0; i < m_clients_vector.size(); i++)
		m_socket->send(pac, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
}


//Update the players positions
void Server::UpdateClientsPos(sf::Packet pac, ClientInfo info)
{
	sf::Vector2f pos;
	//Gets the positon
	pac >> pos;
	for (int i = 0; i < m_clients_vector.size(); i++)
	{
		//Checking for the right client
		if (info.port != m_clients_vector[i]->GetPort() || info.address !=m_clients_vector[i]->GetIp())
		{
			sf::Packet packet;
			packet << UPDATEPOS << pos.x << pos.y;
			//Update the other clients position
			m_socket->send(packet, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
			break;
		}	
	}		
}


void Server::GameEnd(sf::Packet pac, ClientInfo info)
{
	int id = 0;
	pac >> id;
	for (size_t i = 0; i < m_clients_vector.size(); i++)
	{
		sf::Packet packet;

		// If the id was the same as this client then it lost.
		if (id == m_clients_vector[i]->GetId())
		{
			packet << LOSE;
			m_socket->send(packet, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
		}
		// Send to the winning client
		else
		{
			packet << WIN;
			m_socket->send(packet, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
		}
	}
}


//Ready function for player
void Server::Ready(sf::Packet pac, ClientInfo info)
{
	int id = 0;
	sf::Packet packet;
	pac >> id;

	for (size_t i = 0; i < m_clients_vector.size(); i++)
	{
		//Set Client to ready
		if (id == m_clients_vector[i]->GetId())
		{
			m_clients_vector[i]->SetReady(true);
			m_clientReady++;
			std::cout << m_clientReady << std::endl;
			//Check if the other client is not ready
			if (m_clientReady < m_clients_vector.size() || m_clientReady <= 1)
			{
				packet << WAITING;
				m_socket->send(packet, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
				return;
			}
		}
	}

	//Check if all clients is ready
	if (m_clientReady >= m_clients_vector.size() && m_clientReady >= 1)
	{
		for (size_t i = 0; i < m_clients_vector.size(); i++)
		{
			packet << START << true;
			m_socket->send(packet, m_clients_vector[i]->GetIp(), m_clients_vector[i]->GetPort());
		}
	}
}


// Overload for pacet with an vector2f
sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& v)
{
	return packet << v.x << v.y;
}


// Overload for pacet with an vector2f
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v)
{
	return packet >> v.x >> v.y;
}
