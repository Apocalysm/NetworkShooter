#include <string>
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
	packet >> command >> pos.x >> pos.y;

	//Check if we get an position from client
	if (command == 1)
	{
		Connect(adress, port);

		return;
	}

	else if (command == 2)
	{
		//packet >> x >> y;

		UpdateClientsPos(adress, pos);

		return;
	}
}

//Check if an bullet the enemy.
void Server::BulletHit()
{

}

//Update the players positions
void Server::UpdateClientsPos(sf::IpAddress adress, sf::Vector2f pos)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (adress != clients[i]->GetIp())
		{
			sf::Packet packet;
			packet >> pos.x >> pos.y;
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
sf::Packet& operator <<(sf::Packet& packet, const Server& server)
{
	return packet << server.vector.x << server.vector.y;
}

sf::Packet& operator >>(sf::Packet& packet, Server& server)
{
	return packet >> server.vector.x >> server.vector.y;
}