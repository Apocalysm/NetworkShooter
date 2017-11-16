#pragma once
#include <vector>

namespace sf
{
	class IpAdress;
}
class Client;

class Server
{
public:
	Server();
	~Server();

	void Update();

private:
	void Connect();
	void Disconnect();

	std::vector<Client*> clients;
};

