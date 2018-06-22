//
// Created by Brendan Berg on 10.06.18.
//

#ifndef NETWORKGAMETEST_PLAYERHANDLER_HPP
#define NETWORKGAMETEST_PLAYERHANDLER_HPP

#include "player.hpp"
#include "mapHandler.hpp"

#include <common/baseSocket.hpp>

//network
#include <netinet/in.h>
#include <sys/socket.h>
//std
#include <list>
//thread
#include <thread>
#include <mutex>


class PlayerHandler
{
public:
    explicit PlayerHandler(MapHandler* mapHandler);

    ~PlayerHandler();

    void update();

    
private:

    int m_SockFD;
    struct sockaddr_in m_HostAddr;

    BaseSocket m_Socket;

    MapHandler* m_MapHandler;

    std::list<Player*> m_Player;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;
};


#endif //NETWORKGAMETEST_PLAYERHANDLER_HPP
