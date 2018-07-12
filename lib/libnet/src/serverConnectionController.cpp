//
// Created by Brendan Berg on 11.07.18.
//

#include "net/server/serverConnectionController.hpp"


ServerConnectionController::ServerConnectionController(unsigned short hostPort)
    : m_Socket(hostPort)
{
    m_Running = true;
    m_UpdateThread = std::thread([this]{
        this->update();
    });
}

ServerConnectionController::~ServerConnectionController()
{
    m_Running = false;
    m_UpdateThread.join();

    m_NewSessionSocketsMtx.lock();
    for (auto it = m_NewSessionSockets.begin(); it != m_NewSessionSockets.end(); it++)
    {
        delete *it;
        m_NewSessionSockets.erase(it);
    }
    m_NewSessionSocketsMtx.unlock();
}

bool ServerConnectionController::newClientAvailable()
{
    bool ret;

    m_NewSessionSocketsMtx.lock();
    ret = !m_NewSessionSockets.empty();
    m_NewSessionSocketsMtx.unlock();

    return ret;
}

SessionSocket* ServerConnectionController::getNewClient()
{
    SessionSocket* ret = nullptr;

    if (newClientAvailable())
    {
        m_NewSessionSocketsMtx.lock();
        ret = m_NewSessionSockets.front();
        m_NewSessionSockets.pop_front();
        m_NewSessionSocketsMtx.unlock();
    }

    return ret;
}

void ServerConnectionController::update()
{
    SessionSocket* newSocket;

    while (m_Running)
    {
        newSocket = m_Socket.acceptConnection();

        if (newSocket != nullptr)
        {
            m_NewSessionSocketsMtx.lock();
            m_NewSessionSockets.push_back(newSocket);
            m_NewSessionSocketsMtx.unlock();
        }
    }
}
