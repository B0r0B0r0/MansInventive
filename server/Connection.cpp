#include "Connection.h"
#include "DBManipulation.h"
#include <iostream>
#include <sstream>

#define dbi DBManipulation::getInstance()


using namespace std;

Connection* Connection::instance = nullptr;
vector<int> Connection::clienti;

Connection* Connection::getInstance()
{
    if (instance == nullptr)
        instance = new Connection;
    return instance;
}

std::string Connection::modifyDevice(std::string message_p)
{
    //trimit msg la device-uri
    updateDevice(message_p);
    dbi->destroyConnection();
    dbi->initializeConnection();
    dbi->modifyDevice(message_p);
    return (string)"Device modificat cu succes";
}

std::string Connection::deleteAsoc(std::string message_p)
{
    dbi->deleteAsoc(message_p);
    return (string)"Asociere stearsa cu succes";
}

void Connection::updateDevice(std::string message_p)
{

    std::string b = message_p.substr(0, message_p.find(" ", message_p.find(" ") + 1));
    message_p = message_p.substr(message_p.find(" ", message_p.find(" ") + 2));
     for (int i = sockets.size() - 1;i >= 0;i--)
    {
        auto it = find(clienti.begin(), clienti.end(), i);
        if (!(it != clienti.end()))
        {
            sendMessageToClient("WhoDis?", i);
            char buffer[1024];
            size_t received = 0;
            memset(buffer, 0, sizeof(buffer));
            sockets[i]->receive(&buffer, sizeof(buffer), received);
            string sentence(buffer);
            if (sentence == b)
            {
                sendMessageToClient(message_p, i);
                
            }
        }

    }

}

std::string Connection::addAsoc(std::string message_p)
{
    dbi->addAsoc(message_p);
    return (string)"Asociere realizata cu succes";
}

string Connection::messageInterpretor(std::string message_p, int id_Client)
{
    switch (message_p[0])
    {
    case '0':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return registerUser(message_p);
    case '1':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return loginUser(message_p);
    case '2':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return modifyPassword(message_p);
    case '3':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return modifyEmail(message_p);
    case '4':
        message_p = message_p.substr(message_p.find(" ") + 1);

        return deleteUser(message_p);
    case '5':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return addDevice(message_p);
    case '6':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return getDevices(message_p, id_Client);
    case '7':
        message_p = message_p.substr(message_p.find(" ") + 1);
        stopDevice(message_p);
        return (string)"k";
    case '8':
        message_p = message_p.substr(message_p.find(" ") + 1);
        findDevice(message_p);
        return (string)"k";
    case '9':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return deleteDevice(message_p);
    case '/':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return modifyDevice(message_p);
    case '%':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return addAsoc(message_p);
    case '?':
        message_p = message_p.substr(message_p.find(" ") + 1);
        return deleteAsoc(message_p);


    }
}

void Connection::destroyInstance()
{
    if (instance != nullptr)
        delete instance;
}

string Connection::registerUser(std::string message_p)
{
    if (dbi->verifyUser(message_p)=="Not in BD")
        if (dbi->registerUser(message_p))
            return (string)"User inregistrat cu succes";
    return (string)"Userul nu a putut fi inregistrat";
    
}

void Connection::createConnection()
{
    listener.listen(2002);
    selector.add(listener);
}

string Connection::loginUser(string message_p)
{
    string response = dbi->verifyUser(message_p);
    if (response == "Conectat")
    {
        response = dbi->loginUser(message_p);
        return response;
    }
    return response;
}

void Connection::waitForConnection()
{   

    if (selector.wait(sf::seconds(5))) // astept sa se conecteze cineva
    {
        if (selector.isReady(listener)) //asculta daca e gata sa primeasca date
        {
            sf::TcpSocket* socket = new sf::TcpSocket; //creez socket pt a retine conexiunea
            listener.accept(*socket); //verific daca exista conexiunea si daca poate accepta mesaje
            sockets.push_back(socket);
            selector.add(*socket);  //il pot recunoaste la o conectare ulterioara
        }
    }
}

std::string Connection::modifyEmail(std::string message_p)
{
    if (dbi->verifyUser(message_p) == "Conectat")
    {
        dbi->modifyEmail(message_p);
        return (string)"Email Modificat";
    }

    return (string)"Nu s-a putut modifica emailul";
}

void Connection::sendMessageToClient(std::string message_p, int id_client_p)
{
    std::string message = message_p;
    (*sockets[id_client_p]).send(message.c_str(), message.size() + 1);
}

std::string Connection::deleteUser(std::string message_p)
{
    vector<string> results = dbi->getDisp(message_p);
    for (int i = 0;i < results.size();i++)
    {
        string b = results[i].substr(0, results[i].find(" ", results[i].find(" ") + 1));
        stopDevice(b);
    }
    dbi->destroyConnection();
    dbi->initializeConnection();
    dbi->deleteUser(message_p); //inchid hvm deschise
    return (string)"User sters cu succes";
}


void Connection::receiveMessageFromClient()
{
        for (int i = 0; i < sockets.size(); i++) {
           
            if (selector.isReady(*sockets[i]))    //verifica daca asta e socketul de la care a primit mesajul
            {
                
                char buffer[1024];
                size_t received = 0;
                memset(buffer, 0, sizeof(buffer));
                sockets[i]->receive(&buffer, sizeof(buffer), received);
                string sentence(buffer);
                
                if (sentence == "client")
                {
                    clienti.push_back(i);
                    (*sockets[i]).send(sentence.c_str(), sentence.size() + 1);
                    sentence = "";
                }
                
                if (sentence == "disclient")
                {
                    auto it = find(clienti.begin(), clienti.end(), i);

                    if (it != clienti.end()) 
                        clienti.erase(it);
                    (*sockets[i]).send(sentence.c_str(), sentence.size() + 1);
                }

                if (sentence != "")
                {
                    dbi->initializeConnection();
                    cout << sentence << endl;
                    if (sentence[0] != '6')
                        sentence = messageInterpretor(sentence);
                    else
                        sentence = messageInterpretor(sentence, i);
                    if(sentence !="")
                    sendMessageToClient(sentence, i);
                    dbi->destroyConnection();
                }
                
                sentence = "";
                
            }
        }
}

std::string Connection::modifyPassword(std::string message_p)
{
    if (dbi->verifyUser(message_p) == "Conectat")
    {
        dbi->modifyParola(message_p);
        return (string)"Parola Modificata";
    }

    return (string)"Nu s-a putut modifica parola";
}

std::string Connection::addDevice(std::string message_p)
{
    return dbi->insertDispozitiv(message_p);
    
}


void Connection::closeAllConnections()
{
    for (auto it = sockets.begin(); it != sockets.end(); ++it)
    {
        (**it).disconnect();
    }
}

void Connection::startDevice(std::string device_p)
{
    istringstream iss(device_p);
    string id, user,denumire, locatie, parametru1, parametru2;
    iss >>id>>user>> denumire >> locatie >> parametru1 >> parametru2;
    string path = "start C:\\Users\\Ayeleen\\source\\repos\\POOProiectBec\\x64\\Debug\\POOProiectDispozitiv.exe "
        + denumire + " " + locatie + " " + parametru1 + " " + parametru2;
    string cmd = "start cmd /c \"" + path + "\"";
    system(cmd.c_str());



    string cred = denumire + " " + locatie;

    dbi->destroyConnection();
    dbi->initializeConnection();
    dbi->modifyStatus(cred, "1");

}

std::string Connection::stopDevice(std::string message_p)
{
    for (int i = sockets.size() - 1;i >= 0;i--)
    {
        auto it = find(clienti.begin(), clienti.end(), i);
        if (!(it != clienti.end()))
        {
            sendMessageToClient("WhoDis?", i);
            char buffer[1024];
            size_t received = 0;
            memset(buffer, 0, sizeof(buffer));
            sockets[i]->receive(&buffer, sizeof(buffer), received);
            string sentence(buffer);
           
            if (sentence == message_p)
            {
                dbi->destroyConnection();
                dbi->initializeConnection();
                dbi->modifyStatus(sentence, "0");
                sendMessageToClient("ShutDown", i);
                //inchid si in bd
                return (string)"HVM Inchis";
            }
        }

    }
    return (string)"Nu a fost gasit HVM-ul";
}

std::string Connection::findDevice(std::string message_p)
{
    startDevice(dbi->findDevice(message_p));
    return (string)"HVM adaugat cu succes";
}

std::string Connection::deleteDevice(std::string message_p)
{
    dbi->destroyConnection();
    dbi->initializeConnection();
    stopDevice(message_p);
    dbi->deleteDevice(message_p);
    return (string)"Device sters cu succes!";

}

void Connection::closeConnection(int id_client_p)
{
    (*sockets[id_client_p]).disconnect();
}

std::string Connection::getDevices(std::string message_p,int id_Client)
{
    vector<string> results = dbi->getDisp(message_p);
    sendMessageToClient(to_string(results.size()),id_Client);
    for (int i = 0;i < results.size();i++)
    {   
        
        char buffer[4096];
        size_t received = 0;
        memset(buffer, 0, sizeof(buffer));
        sockets[id_Client]->receive(&buffer, sizeof(buffer), received);
        sendMessageToClient(results[i], id_Client);
    }
    dbi->destroyConnection();
    dbi->initializeConnection();
    for (int i = 0;i < results.size();i++)
    {
        //deschid hvm-urile
        if(results[i][results[i].size()-1]=='1')
            startDevice(results[i]);
    }

    return (string)"";
}
