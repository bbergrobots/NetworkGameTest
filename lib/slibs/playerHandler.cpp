//
// Created by Brendan Berg on 10.06.18.
//

#include "playerHandler.hpp"

#include <iostream>
#include <netinet/in.h>


PlayerHandler::PlayerHandler(MapHandler* mapHandler)
    : m_MapHandler(mapHandler)
{
    m_Socket = BaseSocket();
    m_Socket.init();
    m_Socket.setHostPort(1337);
    m_Socket.bindToHost();
    m_Socket.listenForConnections();
    m_Socket.setNonBlocking(true);

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

    while (m_Running)
    {
        newSockFD = m_Socket.acceptConnection((struct sockaddr *) &clientAddr);
        if (newSockFD != -1)
        {
            auto newPlayer = new Player(newSockFD, clientAddr);
            m_Player.push_back(newPlayer);

            newPlayer->sendMap(m_MapHandler->getMap());
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
