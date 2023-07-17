#pragma once
#include <SFML/Network.hpp>
#include <iostream>

class ServerIO
{
private:
	static ServerIO* instance;
	sf::TcpSocket socket;
	ServerIO() {}
	~ServerIO() {}

public:
	static ServerIO& getInstance();
	static void deleteInstance();
	void connect_to_server();
	System::String^ send_receive(std::string message);
	sf::TcpSocket& getSocket() { return socket; }
};
