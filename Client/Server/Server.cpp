#include <string>
#include <iostream>
#include "SFML\Network\UdpSocket.hpp"

#include "Server.h"
#include "Client.h"


Server::Server() : 
	socket(new sf::UdpSocket) 
{
	InitServer();
}


Server::~Server()
{
	delete socket;
}

void Server::Update()
{

	while (true)
	{
		Recive();
	}
}

//Lets the client connect to the server
void Server::Connect(sf::IpAddress adress, unsigned short port)
{
	//Check if 2 clients is allready connected
	if (clients.size() >= 2)
	{
		return;
	}

	//Add a new client to the game
	clients.push_back(new Client(adress, port, 10));
	sf::Packet packet;

	packet << "Connected";

	socket->send(packet, adress, port);
}

void Server::Disconnect(sf::IpAddress adress, unsigned short port)
{
	
}

void Server::Recive()
{
	sf::Packet packet;
	sf::Vector2f pos;
	sf::IpAddress adress;
	int command = 0;
	unsigned short port;

	socket->receive(packet, adress, port);
	packet >> command;

	//Check if we get an position from client
	if (command == 1)
	{
		Connect(adress, port);

		return;
	}

	else if (command == 2)
	{
		packet >> pos.x >> pos.y;
		std::cout << pos.x << std::endl;
		UpdateClientsPos(adress, port, pos);

		return;
	}
}

//Check if an bullet the enemy.
void Server::BulletHit()
{

}

//Update the players positions
void Server::UpdateClientsPos(sf::IpAddress adress, unsigned short port, sf::Vector2f pos)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (port != clients[i]->GetPort())
		{
			sf::Packet packet;
			int command = 2;
			packet << command << pos.x << pos.y;
			
			socket->send(packet, clients[i]->GetIp(), clients[i]->GetPort());
		}	
	}		
}

void Server::InitServer()
{
	socket = new sf::UdpSocket();
	socket->bind(27015);
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