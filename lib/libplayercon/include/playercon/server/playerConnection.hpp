//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERCONNECTION_HPP
#define NETWORKGAMETEST_PLAYERCONNECTION_HPP

#include <sock/sessionSocket.hpp>

#include <thread>


class PlayerConnection
{

public:

    explicit PlayerConnection(SessionSocket* socket);

    ~PlayerConnection();

    bool isClientConnected();


private:

    SessionSocket* m_Socket;

    std::thread m_UpdateThread;

    bool m_Running;

    bool m_ClientConnected;

    void update();
};


#endif //NETWORKGAMETEST_PLAYERCONNECTION_HPP
