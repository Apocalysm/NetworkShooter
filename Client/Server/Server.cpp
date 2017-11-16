#include <string>

#include "Server.h"
#include "Client.h"
#include "SFML\Network.hpp"


Server::Server() : socket(new sf::UdpSocket)
{
}


Server::~Server()
{
	delete socket;
}

void Server::Update()
{
	UpdateClientsPos();
}

//Lets the client connect to the server
void Server::Connect(ClientInfo info)
{
	//Check if 2 clients is allready connected
	if (clients.size() >= 2)
	{
		return;
	}

	//Adds a new client to the game
	clients.push_back(new Client(info.adress, info.port));
	sf::Packet packet;

	packet << "Connected";

	socket->send(packet, info.adress, info.port);
	
}

void Server::Disconnect(ClientInfo info)
{
	
}

void Server::Recive()
{

}

//Check if an bullet the enemy.
void Server::BulletHit()
{

}

//Update the players positions
void Server::UpdateClientsPos()
{
	for (int i = 0; i < clients.size(); i++)
	{
		sf::Packet packet;

		packet << clients[i]->GetPos();
		//socket->send(sf::Packet&("clie"), )
	}
		
}
