#pragma once
#include <vector>
#include <map>
#include <functional>
#include "SFML\System\Vector2.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\IpAddress.hpp"
#include "SFML\Graphics\CircleShape.hpp"

enum COMMAND{CONNECT = 0, UPDATEPOS = 1, DISCONNECT = 2, BULLET = 3, SERVERFULL = 4};

struct ClientInfo
{
	sf::IpAddress adress;
	unsigned short port;
};

class Client;

class Bullet;

class Server
{
public:
	Server();
	~Server();

	void Update();

	void InitServer();
private:
	void Connect(sf::Packet packet,ClientInfo info);
	void Disconnect(sf::Packet packet, ClientInfo info);
	void Receive();
	void CreateBullet(sf::Packet packet, ClientInfo info);
	void UpdateClientsPos(sf::Packet packet, ClientInfo info);

	std::vector<Client*> clients;
	std::vector<Bullet*> bullets;
	sf::UdpSocket* socket;
	std::vector<std::function<void(sf::Packet, ClientInfo)>> functionsVector;

};

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);


