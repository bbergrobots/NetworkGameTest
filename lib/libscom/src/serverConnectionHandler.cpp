//
// Created by Brendan Berg on 10.07.18.
//

#include "scom/client/serverConnectionHandler.hpp"

#include <iostream>


ServerConnectionHandler::ServerConnectionHandler(const char* serverAddress, short serverPort)
    : m_Socket(serverAddress, serverPort)
{

}

ServerConnectionHandler::~ServerConnectionHandler()
{
    m_Running = false;
    m_UpdateThread.join();
}

void ServerConnectionHandler::registerServerMessageReceiver(ServerMessageReceiver* serverMessageReceiver)
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
    int length;
    // TODO: create recv data class
    unsigned char buffer[1024];

    while (m_Running && m_ServerConnected)
    {
        length = m_Socket.receiveData(&buffer[0], 1024);

        switch (length)
        {
            case -1:
                break;
            case 0:
                std::cout << "Server disconnected!\n";
                m_ServerConnected = false;
                break;
            case 1:
            case 2:
                break;
            default:
                printReceiveBuffer(buffer, length);

                unsigned short dataHeader = buffer[0];
                dataHeader = dataHeader << 8u;
                dataHeader |= buffer[1];

                int dataLength = length - 2;

                for (auto smr : m_ServerMessageReceiver)
                {
                    if (smr->canProcessData(dataHeader, dataLength))
                    {
                        smr->processData(&buffer[0], dataLength);
                    }
                }

                // TODO: remove
                const char *msg = "Hello, world!";
                m_Socket.sendData(msg, 13);
                break;
        }
    }
}

void ServerConnectionHandler::printReceiveBuffer(unsigned char* rawData, int length) const
{
    std::cout << std::hex;
    std::cout << "Receiving message from server:\n";
    std::cout << "    Header: " << static_cast<short>(rawData[0]) << ' ' << static_cast<short>(rawData[1]) << '\n';
    std::cout << "    Data  : ";

    for (int i = 2; i < length; i++)
    {
        if (((i - 2) % 8 == 0) && (i != 2))
        {
            std::cout << "            ";
        }
        std::cout << static_cast<short>(rawData[i]) << ' ';
        if (((i - 1) % 8 == 0) && ((i+1) != length))
        {
            std::cout << '\n';
        }
    }

    std::cout << '\n';
    std::cout << std::dec;
}
