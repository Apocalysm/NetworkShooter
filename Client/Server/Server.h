#pragma once
#include <vector>
#include <map>

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

private:
	void Connect(ClientInfo info);
	void Disconnect(ClientInfo info);
	void Recive();
	void BulletHit();
	void UpdateClientsPos();

	std::vector<Client*> clients;
	sf::UdpSocket* socket;
	
	
};

