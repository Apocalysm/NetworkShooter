#pragma once
#include <vector>
#include <map>
#include "SFML\System\Vector2.hpp"

namespace sf
{
	class IpAddress;
	class UdpSocket;
}

struct ClientInfo
{
	sf::IpAddress* adress;
	unsigned short port;
};

class Client;

class Server
{
public:
	Server();
	~Server();

	void Update();

	friend sf::Packet& operator <<(sf::Packet& packet, const Server& character);
	sf::Vector2f vector;
private:
	void Connect(ClientInfo info);
	void Disconnect(ClientInfo info);
	void Recive();
	void BulletHit();
	void UpdateClientsPos();

	std::vector<Client*> clients;
	sf::UdpSocket* socket;

};

//Overload for paket with an vector2f
sf::Packet& operator <<(sf::Packet& packet, const Server& server)
{
	return packet << server.vector.x << server.vector.y;
	
}
