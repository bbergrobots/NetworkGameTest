//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/playerNetworkComponent.hpp"

#include <iostream>

PlayerNetworkComponent::PlayerNetworkComponent(SessionSocket* socket)
    : m_Socket(socket), m_MessageContainer(1024), m_ReceiveQueue(4096)
{
    m_ClientConnected = true;
}

PlayerNetworkComponent::~PlayerNetworkComponent()
{
    delete m_Socket;
}

bool PlayerNetworkComponent::isClientConnected()
{
    return m_ClientConnected;
}

int PlayerNetworkComponent::getFileDescriptor()
{
    return m_Socket->getFileDescriptor();
}

void PlayerNetworkComponent::update()
{
    if (m_ClientConnected)
    {
        if (m_ReceiveQueue.receive(m_Socket) == 0)
        {
            std::cout << "Client with file descriptor " << m_Socket->getFileDescriptor() << " disconnected\n\n";
            m_ClientConnected = false;
        }
        else
        {
            while (m_ReceiveQueue.messageReadyForProcessing())
            {
                m_ReceiveQueue.getMessage(&m_MessageContainer);
                m_MessageContainer.print();
            }
        }
    }
}
