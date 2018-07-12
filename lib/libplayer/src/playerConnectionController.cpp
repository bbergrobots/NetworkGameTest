//
// Created by Brendan Berg on 11.07.18.
//

#include "player/server/playerConnectionController.hpp"

#include "player/server/playerController.hpp"


PlayerConnectionController::PlayerConnectionController(unsigned short hostPort)
    : m_ClientConnectionHandler(hostPort)
{
    m_Running = true;
    m_UpdateThread = std::thread([this] {
        this->update();
    });
}

PlayerConnectionController::~PlayerConnectionController()
{
    m_Running = false;
    m_UpdateThread.join();

    for (auto it = m_PlayerConnections.begin(); it != m_PlayerConnections.end(); it++)
    {
        delete *it;
        m_PlayerConnections.erase(it);
    }
}

void PlayerConnectionController::update()
{
    while (m_Running)
    {
        if (m_ClientConnectionHandler.newClientAvailable())
        {
            auto newPlayerController = new PlayerController(m_ClientConnectionHandler.getNewClient());
            m_PlayerConnections.push_back(newPlayerController);
        }

        for (auto it = m_PlayerConnections.begin(); it != m_PlayerConnections.end(); it++)
        {
            if (!(*it)->isClientConnected())
            {
                delete *it;
                m_PlayerConnections.erase(it);
            }
        }
    }
}
