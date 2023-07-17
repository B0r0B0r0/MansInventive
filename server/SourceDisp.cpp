#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>
#include<Windows.h>
#include <string>

using namespace std;

LPCWSTR stringToLPCWSTR(const std::string& str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* buffer = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
    return buffer;
}

int main(int argc, char *argv[])
{
    

    if (argc < 4)
        return 0;

    string denumire(argv[1]), locatie(argv[2]), parametru1(argv[3]), parametru2(argv[4]);
    string messageRcv="";
    string crd = denumire +" " + locatie;
    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, stringToLPCWSTR(crd));
    if (hMutex != NULL)
    {
        // Mutex already exists, another instance is running
        CloseHandle(hMutex);
        return 0;
    }

    // Create named mutex
    hMutex = CreateMutex(NULL, TRUE, stringToLPCWSTR(crd));

    sf::TcpSocket socket;
    cerr << denumire << " " << locatie<<endl;
    // Connect to the server
  
        if (socket.connect("localhost", 2002) == sf::Socket::Done)
        {
            while (true)
            {
            std::cout << "Connected to server" << std::endl;

            // Send a message to the server


            // Receive a response from the server
            char buffer[1024];
            size_t received;
            if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done)
            {

                messageRcv = buffer;
                std::cout << "Received " << received << " bytes from server: " << buffer << std::endl;
            }
            else
            {
                std::cerr << "Failed to receive response from server" << std::endl;
            }

            if (messageRcv != "")
            {
                if (messageRcv == "ShutDown")
                {
                    socket.disconnect();
                    return 0;
                }
                else
                    if (messageRcv == "WhoDis?")
                    {
                    hello:
                        string message = denumire + " " + locatie;
                        if (socket.send(message.c_str(), message.length() + 1) == sf::Socket::Done)
                        {
                            std::cout << "Sent message to server" << std::endl;
                        }
                        else
                        {
                            std::cerr << "Failed to send message to server" << std::endl;
                            goto hello;
                        }
                    }
                    else
                    {
                        size_t pos = 0;
                        pos = messageRcv.find(" ");
                        parametru1 = messageRcv.substr(0, pos);

                        // extrag denumirea
                        messageRcv = messageRcv.substr(pos + 1);
                        pos = messageRcv.find(" ");
                        parametru2 = messageRcv.substr(0, pos);
                        cerr << parametru1 << " " << parametru2;
                    }
            }
            }

        }
        else
        {
            std::cerr << "Failed to connect to server" << std::endl;
        }
    

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
   
    return 0;
}