//
// Created by Brendan Berg on 10.06.18.
//

#include "playerHandler.hpp"

#include <iostream>
#include <cassert>
#include <fcntl.h>
#include <unistd.h>


PlayerHandler::PlayerHandler(MapHandler* mapHandler)
    : m_MapHandler(mapHandler)
{
    int ret, tmp, yes = 1;

    // create socket
    m_SockFD = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_SockFD != -1);

    // set socket options
    ret = setsockopt(m_SockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    assert(ret != -1);

    // assign address information to socket
    m_HostAddr.sin_family = AF_INET;
    m_HostAddr.sin_port = htons(1337);
    m_HostAddr.sin_addr.s_addr = 0; // auto address
    memset(&(m_HostAddr.sin_zero), '\0', 8);

    // bind socket to address
    ret = bind(m_SockFD, (struct sockaddr *) &m_HostAddr, sizeof(struct sockaddr));
    assert(ret != -1);

    // enable listening to network connections
    ret = listen(m_SockFD, 8);
    assert(ret != -1);


    // set non-blocking mode
    tmp = fcntl(m_SockFD, F_GETFL);
    tmp |= O_NONBLOCK;
    fcntl(m_SockFD, F_SETFL, tmp);

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
    for (auto &it : m_Player)
    {
        delete it;
    }

    // TODO: Test IDE warnings with following code
//    for (auto it = m_Player.begin(); it != m_Player.end(); it++)
//    {
//        delete it;
//    }

    close(m_SockFD);
}

void PlayerHandler::update()
{
    socklen_t sockInSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddr{};
    int newSockFD;

    while (m_Running)
    {
        newSockFD = accept(m_SockFD, (struct sockaddr *) &clientAddr, &sockInSize);
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
