#pragma once
#include <vector>

#include <map>
#include <functional>

#include "SFML\System\Vector2.hpp"
#include "SFML\Network\Packet.hpp"
#include "SFML\Network\IpAddress.hpp"
#include "SFML\Graphics\CircleShape.hpp"

enum COMMAND{
	CONNECT = 0,
	UPDATEPOS = 1,
	DISCONNECT = 2,
	NEWBULLET = 3,
	SERVERFULL = 4,
	BULLETPOS = 5,
	END = 6,
	WIN = 7,
	LOSE = 8,
	READY = 9,
	WAITING = 10,
	START = 11
};

struct ClientInfo
{
	sf::IpAddress address;
	unsigned short port;
	int id;
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
	typedef std::pair<COMMAND, std::function<void(sf::Packet, ClientInfo)>> CommandPair;
	std::map<COMMAND, std::function<void(sf::Packet, ClientInfo)>> functions_map;

	void Connect(sf::Packet pac, ClientInfo info);
	void Disconnect(sf::Packet pac, ClientInfo info);
	void Receive();
	void CreateBullet(sf::Packet pac, ClientInfo info);
	void UpdateClientsPos(sf::Packet pac, ClientInfo info);
	void GameEnd(sf::Packet pac, ClientInfo info);
	void Ready(sf::Packet pac, ClientInfo info);

	std::vector<Client*> m_clients_vector;
	std::vector<Bullet*> m_bullets_vector;
	sf::UdpSocket* m_socket;
	int m_clientReady;
};

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v);