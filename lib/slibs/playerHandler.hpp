//
// Created by Brendan Berg on 10.06.18.
//

#ifndef NETWORKGAMETEST_PLAYERHANDLER_HPP
#define NETWORKGAMETEST_PLAYERHANDLER_HPP

#include "player.hpp"
#include <map/baseMap.hpp>

#include <sock/listeningSocket.hpp>
#include <sock/baseSocket.hpp>

//std
#include <list>
//thread
#include <thread>
#include <mutex>


class PlayerHandler
{
public:
    explicit PlayerHandler(BaseMap* map);

    ~PlayerHandler();

    void update();

    
private:

    ListeningSocket m_Socket;

    BaseMap* m_Map;

    std::list<Player*> m_Player;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;
};


#endif //NETWORKGAMETEST_PLAYERHANDLER_HPP
