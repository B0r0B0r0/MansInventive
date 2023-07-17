#include "ServerIO.h"

ServerIO* ServerIO::instance = nullptr;

ServerIO& ServerIO::getInstance()
{
    if (!ServerIO::instance)
    {
        ServerIO::instance = new ServerIO();
    }
    return (*ServerIO::instance);
}

void ServerIO::deleteInstance()
{
    if (ServerIO::instance != nullptr)
    {
        delete ServerIO::instance;
        ServerIO::instance = nullptr;
    }
}

void ServerIO::connect_to_server()
{
    if (socket.connect("192.168.237.133", 2002) == sf::Socket::Done)
        return;
    else
        connect_to_server();
}

System::String^ ServerIO::send_receive(std::string message)
{
    char buffer[1024];
    size_t received;

    hello:
    if (socket.send(message.c_str(), message.length() + 1) == sf::Socket::Done)
    {
        std::cout << "Sent message to server" << std::endl;
    }
    else
    {
        std::cerr << "Failed to send message to server" << std::endl;
        goto hello;
    }

    if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
    {
        System::String^ managedString = gcnew System::String(buffer);
        //System::Windows::Forms::MessageBox::Show(managedString);
        std::cout << "Received " << received << " bytes from server: " << buffer << std::endl;
        return managedString;
    }
    else
    {
        std::cerr << "Failed to receive response from server" << std::endl;
    }
}
