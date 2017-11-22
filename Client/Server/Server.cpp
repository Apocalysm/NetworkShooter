#include <string>
#include <iostream>
#include "SFML\Network\UdpSocket.hpp"

#include "Server.h"
#include "Client.h"


Server::Server() : 
	socket(new sf::UdpSocket) 
{
	//Putting the functions in the vector
	functionsVector.push_back(std::bind(&Server::Connect, this,std::placeholders::_1, std::placeholders::_2));
	functionsVector.push_back(std::bind(&Server::UpdateClientsPos, this, std::placeholders::_1, std::placeholders::_2));
	functionsVector.push_back(std::bind(&Server::Disconnect, this, std::placeholders::_1, std::placeholders::_2));
	functionsVector.push_back(std::bind(&Server::BulletHit, this, std::placeholders::_1, std::placeholders::_2));
	//Creates the server
	InitServer();
}


Server::~Server()
{
	delete socket;
}

//Update the server
void Server::Update()
{
	while (true)
	{
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

		socket->send(packet, info.adress, info.port);
		return;
	}

	//Add a new client to the game
	clients.push_back(new Client(info.adress, info.port, 10));

	packet << "Connected";

	socket->send(packet, info.adress, info.port);
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
			continue;
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
	socket->receive(packet, info.adress, info.port);
	//Getting which command
	packet >> command;
	//Calls the function
	functionsVector[command](packet,info);

}

//Check if an bullet the enemy.
void Server::BulletHit(sf::Packet packet, ClientInfo info)
{

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