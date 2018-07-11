//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
#define NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP

#include "com/messageReceiver.hpp"
#include "com/messageContainer.hpp"

#include <sock/clientSocket.hpp>

#include <list>
#include <thread>


class ServerConnectionHandler
{

public:

    ServerConnectionHandler(const char* serverAddress, unsigned short serverPort);

    ~ServerConnectionHandler();

    void registerServerMessageReceiver(MessageReceiver* serverMessageReceiver);

    void establishConnection();

    bool isServerConnected() const;


private:

    ClientSocket m_Socket;

    std::thread m_UpdateThread;

    bool m_Running;

    bool m_ServerConnected;

    std::list<MessageReceiver*> m_ServerMessageReceiver;

    std::list<MessageContainer> m_MessageDispatchQueue;

    void update();


};


#endif //NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
