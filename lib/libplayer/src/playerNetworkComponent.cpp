//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/playerNetworkComponent.hpp"

#include <iostream>
#include <string>


PlayerNetworkComponent::PlayerNetworkComponent(SessionSocket* socket)
    : m_Socket(socket), m_MessageContainer(1024), m_ReceiveQueue(4096), m_SendQueue(4096)
{
    m_ClientConnected = true;
}

PlayerNetworkComponent::~PlayerNetworkComponent()
{
    delete m_Socket;
}

bool PlayerNetworkComponent::isClientConnected() const
{
    return m_ClientConnected;
}

int PlayerNetworkComponent::getFileDescriptor() const
{
    return m_Socket->getFileDescriptor();
}

void PlayerNetworkComponent::sendMessage(MessageContainer* messageContainer)
{
    std::string label = "Send message to player ";
    label += std::to_string(m_Socket->getFileDescriptor());
    messageContainer->print(label);
    m_SendQueue.setMessage(messageContainer);
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
                std::string label = "Received message from player ";
                label += std::to_string(m_Socket->getFileDescriptor());
                m_ReceiveQueue.getMessage(&m_MessageContainer);
                m_MessageContainer.print(label);
                // TODO: distribute message to message receivers
            }

            while (m_SendQueue.messageReadyForSending())
            {
                m_SendQueue.send(m_Socket);
            }
        }
    }
}
