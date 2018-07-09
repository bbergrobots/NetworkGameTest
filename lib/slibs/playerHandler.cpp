//
// Created by Brendan Berg on 10.06.18.
//

#include "playerHandler.hpp"

#include <iostream>
#include <netinet/in.h>


PlayerHandler::PlayerHandler(BaseMap* map)
    : m_Map(map), m_Socket(1337)
{
    // start update thread
    m_RunningMutex.lock();
    m_Running = true;
    m_RunningMutex.unlock();
    m_UpdateThread = std::thread([this]{
        this->update();
    });
}

PlayerHandler::~PlayerHandler()
{
    // deactivate update thread
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

    // destroy players
    for (auto it = m_Player.begin(); it != m_Player.end(); it++)
    {
        delete *it;
        m_Player.erase(it);
    }

    m_Socket.closeSocket();
}

void PlayerHandler::update()
{
    struct sockaddr_in clientAddr{};
    int newSockFD;

    SessionSocket* newSock;

    while (m_Running)
    {
        newSock = m_Socket.acceptConnection();

        if (newSock != nullptr)
        {
            auto newPlayer = new Player(newSock);
            m_Player.push_back(newPlayer);

            newPlayer->sendMap(m_Map->getMapData());
        }

        for (auto it = m_Player.begin(); it != m_Player.end(); it++)
        {
            if (not (*it)->isClientConnected())
            {
                delete *it;
                m_Player.erase(it);
            }
        }
    }
}
