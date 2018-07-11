//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_CLIENTCONNECTIONHANDLER_HPP
#define NETWORKGAMETEST_CLIENTCONNECTIONHANDLER_HPP

#include <sock/listeningSocket.hpp>
#include <sock/sessionSocket.hpp>

#include <list>
#include <mutex>
#include <thread>


class ClientConnectionHandler
{

public:

    explicit ClientConnectionHandler(unsigned short hostPort);

    ~ClientConnectionHandler();

    bool newClientAvailable();

    SessionSocket* getNewClient();


private:

    ListeningSocket m_Socket;

    std::thread m_UpdateThread;

    bool m_Running;

    std::mutex m_NewSessionSocketsMtx;

    std::list<SessionSocket*> m_NewSessionSockets;

    void update();
};


#endif //NETWORKGAMETEST_CLIENTCONNECTIONHANDLER_HPP
