#include <string>
#include <iostream>
#include "SFML\Network\UdpSocket.hpp"

#include "Bullet.h"
#include "Server.h"
#include "Client.h"
#include "SFML\System\Vector2.hpp"



Server::Server() : 
	m_socket(new sf::UdpSocket) 
{
	//Putting the functions in the vector
	functionsMap.insert(commandPair(CONNECT, std::bind(&Server::Connect, this, std::placeholders::_1, std::placeholders::_2)));
	functionsMap.insert(commandPair(UPDATEPOS, std::bind(&Server::UpdateClientsPos, this, std::placeholders::_1, std::placeholders::_2)));
	functionsMap.insert(commandPair(DISCONNECT, std::bind(&Server::Disconnect, this, std::placeholders::_1, std::placeholders::_2)));
	functionsMap.insert(commandPair(BULLET, std::bind(&Server::CreateBullet, this, std::placeholders::_1, std::placeholders::_2)));
	//Creates the server
	InitServer();
}


Server::~Server()
{
	delete m_socket;
}

//Update the server
void Server::Update()
{
	while (true)
	{
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			if ((*it)->GetDestroy() == true)
			{
				delete(*it);
				bullets.erase(it);
			}
			it++;
		}

		//Update every bullet position
		/*for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Update();

			for (size_t j = 0; j < clients.size(); j++)
			{
				sf::Packet packet;
				packet << BULLETPOS << bullets[i]->GetPos();
				m_socket->send(packet, clients[j]->GetIp(), clients[j]->GetPort());
			}
		}*/
		
		Receive();
	}
}

//Lets the client connect to the server
void Server::Connect(sf::Packet pack, ClientInfo info)
{
	sf::Packet packet;

	//Check if 2 clients is allready connected
	if (clients.size() >= 2)
	{
		packet << SERVERFULL << "The server is full!";

		m_socket->send(packet, info.adress, info.port);
		return;
	}
	//Add a new client to the game
	
	if (clients.size() < 1)
	{
		clients.push_back(new Client(info.adress, info.port, 1));
		sf::Vector2f startPos = sf::Vector2f(150, 360);
		packet << CONNECT << startPos;
		m_socket->send(packet, info.adress, info.port);
		return;
	}
	clients.push_back(new Client(info.adress, info.port, 2));
	sf::Vector2f startPos = sf::Vector2f(1130, 360);
	packet << CONNECT << startPos;
	m_socket->send(packet, info.adress, info.port);


}

//Disconnect from the server
void Server::Disconnect(sf::Packet packet, ClientInfo info)
{
	for (auto it = clients.begin(); it != clients.end();)
	{
		//Check if we have the right client
		if ((*it)->GetIp() == info.adress && (*it)->GetPort() == info.port)
		{
			//Delete the client from the vector
			delete (*it);
			clients.erase(it);
			break;
		}
		it++;
	}
}

//Receive from the client
void Server::Receive()
{
	sf::Packet packet;
	ClientInfo info;

	int command = 0;

	//Getting the data from the Client
	m_socket->receive(packet, info.adress, info.port);
	//Getting which command
	packet >> command;
	COMMAND cd = static_cast<COMMAND>(command);

	//Calls the function
	functionsMap[cd](packet, info);

}

//Update for bulletPosition
void Server::CreateBullet(sf::Packet packet, ClientInfo info)
{
	sf::Vector2f mousepos;
	sf::Vector2f pos;
	packet >> mousepos >> pos;
	bullets.push_back(new Bullet(pos, mousepos));

	packet << BULLET << mousepos << pos;
	for (size_t i = 0; i < clients.size(); i++)
		m_socket->send(packet, clients[i]->GetIp(), clients[i]->GetPort());
}

//Update the players positions
void Server::UpdateClientsPos(sf::Packet packet, ClientInfo info)
{
	sf::Vector2f pos;
	//Gets the positon
	packet >> pos;
	for (int i = 0; i < clients.size(); i++)
	{
		//Checking for the right client
		if (info.port != clients[i]->GetPort() || info.adress !=clients[i]->GetIp())
		{
			sf::Packet packet;
			packet << UPDATEPOS << pos.x << pos.y;
			//Update the other clients position
			m_socket->send(packet, clients[i]->GetIp(), clients[i]->GetPort());
			break;
		}	
	}		
}

void Server::InitServer()
{
	m_socket = new sf::UdpSocket();
	m_socket->bind(27015);
}

//Overload for paket with an vector2f
sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& v)
{
	return packet << v.x << v.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v)
{
	return packet >> v.x >> v.y;
}
