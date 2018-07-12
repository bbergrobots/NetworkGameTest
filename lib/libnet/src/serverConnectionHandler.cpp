//
// Created by Brendan Berg on 10.07.18.
//

#include "net/client/serverConnectionHandler.hpp"

#include "net/receiveQueue.hpp"

#include <iostream>


ServerConnectionHandler::ServerConnectionHandler(const char* serverAddress, unsigned short serverPort)
    : m_Socket(serverAddress, serverPort)
{

}

ServerConnectionHandler::~ServerConnectionHandler()
{
    m_Running = false;
    m_UpdateThread.join();
}

void ServerConnectionHandler::registerServerMessageReceiver(MessageReceiverInterface* serverMessageReceiver)
{
    m_ServerMessageReceiver.push_back(serverMessageReceiver);
}

void ServerConnectionHandler::establishConnection()
{
    m_Socket.establishConnection();
    m_ServerConnected = true;
    m_Running = true;
    m_UpdateThread = std::thread([this] {
       this->update();
    });
}

bool ServerConnectionHandler::isServerConnected() const
{
    return m_ServerConnected;
}

void ServerConnectionHandler::update()
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
