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
	void Connect(sf::IpAddress address, unsigned short port);
	void Disconnect(sf::IpAddress address, unsigned short port);
	void Recive();
	void BulletHit();
	void UpdateClientsPos(sf::IpAddress address, unsigned short port ,sf::Vector2f pos);

	std::vector<Client*> clients;
	sf::UdpSocket* socket;

};

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);

