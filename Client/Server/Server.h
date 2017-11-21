#pragma once
#include <vector>
#include <map>
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\IpAddress.hpp"

struct ClientInfo
{
	sf::IpAddress adress;
	unsigned short port;
};

class Client;

class Server
{
public:
	Server();
	~Server();

	void Update();

	
	sf::Vector2f vector;
	void InitServer();
private:
	void Connect(sf::IpAddress adress, unsigned short port);
	void Disconnect(sf::IpAddress adress, unsigned short port);
	void Recive();
	void BulletHit();
	void UpdateClientsPos(sf::IpAddress adress, sf::Vector2f pos);

	std::vector<Client*> clients;
	sf::UdpSocket* socket;

};

sf::Packet& operator <<(sf::Packet& packet, const Server& character);
sf::Packet& operator >>(sf::Packet& packet, Server& server);

