//
// Created by Brendan Berg on 11.07.18.
//

#include "plctrl/server/playerConnection.hpp"

#include <com/messageContainer.hpp>
#include <com/receiveQueue.hpp>

#include <iostream>


PlayerConnection::PlayerConnection(SessionSocket* socket)
    : m_Socket(socket), m_SendQueue(8192)
{
    std::cout << "Construct player with file descriptor " << m_Socket->getFileDescriptor() << ":\n";
    std::cout << "   Address: " << m_Socket->getClientAddress() << '\n';
    std::cout << "      Port: " << m_Socket->getClientPort() << "\n\n";

    m_ClientConnected = true;

    m_Running = true;
    m_UpdateThread = std::thread([this] {
        this->update();
    });
}

PlayerConnection::~PlayerConnection()
{
    std::cout << "Destruct player with file descriptor " << m_Socket->getFileDescriptor() << "\n\n";

    m_Running = false;
    m_UpdateThread.join();

    delete m_Socket;
}

bool PlayerConnection::isClientConnected()
{
    return m_ClientConnected;
}

void PlayerConnection::update()
{
    MessageContainer msgContainer(1024);
    ReceiveQueue recvBuffer(4096);

    while (m_Running && m_ClientConnected)
    {
        if (recvBuffer.receive(m_Socket) == 0)
        {
            std::cout << "Client with file descriptor " << m_Socket->getFileDescriptor() << " disconnected\n\n";
            m_ClientConnected = false;
        }
        else
        {
            while (recvBuffer.messageReadyForProcessing())
            {
                recvBuffer.getMessage(&msgContainer);
                msgContainer.print();
            }

            if (m_SendQueue.messageReadyForSending())
            {
                m_SendQueue.send(m_Socket);
            }
        }
    }
}
