//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/playerListener.hpp"

#include <sock/sessionSocket.hpp>


PlayerListener::PlayerListener(unsigned short hostPort)
    : m_ConnectionHandler(hostPort)
{

}

bool PlayerListener::newPlayerAvailable()
{
    return m_ConnectionHandler.newClientAvailable();
}

PlayerNetworkComponent* PlayerListener::getNewPlayerNetworkComponent()
{
    PlayerNetworkComponent* newNetworkComponent = nullptr;

    if (newPlayerAvailable())
    {
        SessionSocket* newSessionSocket = m_ConnectionHandler.getNewClient();
        newNetworkComponent = new PlayerNetworkComponent(newSessionSocket);
    }

    return newNetworkComponent;
}
