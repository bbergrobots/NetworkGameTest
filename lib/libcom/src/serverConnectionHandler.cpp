//
// Created by Brendan Berg on 10.07.18.
//

#include "com/client/serverConnectionHandler.hpp"

#include "com/receiveBufferQueue.hpp"

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

void ServerConnectionHandler::registerServerMessageReceiver(MessageReceiver* serverMessageReceiver)
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
    ReceiveBufferQueue recvBuffer(4096);


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
                recvBuffer.encloseMessage(&msgContainer);
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
