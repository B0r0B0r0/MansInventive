#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include<Windows.h>


class Connection
{
	static Connection* instance;
	static std::vector<int> clienti;
	Connection() {}
	~Connection() {}

	sf::TcpListener listener;
	sf::SocketSelector selector;
	std::vector<sf::TcpSocket*> sockets;

	std::string messageInterpretor(std::string message_p, int id_Client=0);

	LPWSTR stringToLPWSTR(const std::string& str);
	
	std::string registerUser(std::string message_p);
	std::string loginUser(std::string message_p);
	std::string modifyPassword(std::string message_p);
	std::string modifyEmail(std::string message_p);
	std::string deleteUser(std::string message_p);
	std::string addDevice(std::string message_p);
	std::string getDevices(std::string message_p,int id_Client);
	std::string stopDevice(std::string message_p);
	std::string findDevice(std::string message_p);
	std::string deleteDevice(std::string message_p);
	std::string modifyDevice(std::string message_p);
	std::string addAsoc(std::string message_p);
	std::string deleteAsoc(std::string message_p);
	void updateDevice(std::string message_p);


	void startDevice(std::string device_p);
	

public:
	static Connection* getInstance();
	static void destroyInstance();

	void createConnection();
	void waitForConnection();
	void sendMessageToClient(std::string message_p, int id_client_p);
	void receiveMessageFromClient();
	void closeConnection(int id_client_p);
	void closeAllConnections();


};

