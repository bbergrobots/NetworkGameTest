//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERCONNECTIONCONTROLLER_HPP
#define NETWORKGAMETEST_PLAYERCONNECTIONCONTROLLER_HPP

#include "player/server/playerConnection.hpp"

#include <net/server/clientConnectionHandler.hpp>

#include <list>
#include <thread>


class PlayerConnectionController
{

public:

    explicit PlayerConnectionController(unsigned short hostPort);

    ~PlayerConnectionController();


private:

    ClientConnectionHandler m_ClientConnectionHandler;

    std::list<PlayerConnection*> m_PlayerConnections;

    std::thread m_UpdateThread;

    bool m_Running;

    void update();


};


#endif //NETWORKGAMETEST_PLAYERCONNECTIONCONTROLLER_HPP
