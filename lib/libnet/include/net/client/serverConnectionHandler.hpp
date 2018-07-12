//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
#define NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP

#include "net/messageReceiverInterface.hpp"
#include "net/messageContainer.hpp"

#include <sock/clientSocket.hpp>

#include <list>
#include <thread>


class ServerConnectionHandler
{

public:

    ServerConnectionHandler(const char* serverAddress, unsigned short serverPort);

    ~ServerConnectionHandler();

    void registerServerMessageReceiver(MessageReceiverInterface* serverMessageReceiver);

    void establishConnection();

    bool isServerConnected() const;


private:

    ClientSocket m_Socket;

    std::thread m_UpdateThread;

    bool m_Running;

    bool m_ServerConnected;

    std::list<MessageReceiverInterface*> m_ServerMessageReceiver;

    std::list<MessageContainer> m_MessageDispatchQueue;

    void update();


};


#endif //NETWORKGAMETEST_SERVERCONNECTIONHANDLER_HPP
