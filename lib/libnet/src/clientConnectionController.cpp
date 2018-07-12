//
// Created by Brendan Berg on 10.07.18.
//

#include "net/client/clientConnectionController.hpp"

#include "net/receiveQueue.hpp"

#include <iostream>


ClientConnectionController::ClientConnectionController(const char* serverAddress, unsigned short serverPort)
    : m_Socket(serverAddress, serverPort)
{

}

ClientConnectionController::~ClientConnectionController()
{
    if (m_Running)
    {
        m_Running = false;
        m_UpdateThread.join();
    }
}

void ClientConnectionController::registerServerMessageReceiver(MessageReceiverInterface* serverMessageReceiver)
{
    m_ServerMessageReceiver.push_back(serverMessageReceiver);
}

void ClientConnectionController::establishConnection()
{
    m_Socket.establishConnection();
    m_ServerConnected = true;
    m_Running = true;
    m_UpdateThread = std::thread([this] {
       this->update();
    });
}

bool ClientConnectionController::isServerConnected() const
{
    return m_ServerConnected;
}

void ClientConnectionController::update()
{
    MessageContainer msgContainer(1024);
    ReceiveQueue recvBuffer(4096);


    while (m_Running && m_ServerConnected)
    {
        if (recvBuffer.receive(&m_Socket) == 0)
        {
            std::cout << "Server disconnected!\n\n";
            m_ServerConnected = false;
        }
        else
        {
            while (recvBuffer.messageReadyForProcessing())
            {
                recvBuffer.getMessage(&msgContainer);
                msgContainer.print();

                for (auto smr : m_ServerMessageReceiver)
                {
                    if (smr->canProcessData(&msgContainer))
                    {
                        smr->processData(&msgContainer);
                    }
                }
            }
        }
    }
}
