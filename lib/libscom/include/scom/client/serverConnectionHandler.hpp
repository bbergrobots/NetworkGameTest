//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
#define NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP

#include "serverMessageReceiver.hpp"

#include <sock/clientSocket.hpp>

#include <list>
#include <thread>


class ServerConnectionHandler
{

public:

    ServerConnectionHandler(const char* serverAddress, short serverPort);

    ~ServerConnectionHandler();

    void registerServerMessageReceiver(ServerMessageReceiver* serverMessageReceiver);

    void establishConnection();

    bool isServerConnected() const;


private:

    ClientSocket m_Socket;

    std::thread m_UpdateThread;

    bool m_Running;

    bool m_ServerConnected;

    std::list<ServerMessageReceiver*> m_ServerMessageReceiver;

    void update();

    // TODO: remove
    void printReceiveBuffer(unsigned char *rawData, int length) const;


};


#endif //NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
