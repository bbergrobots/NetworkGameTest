//
// Created by Brendan Berg on 16.06.18.
//

#include "serverHandler.hpp"

#include <iostream>
#include <cstdlib>


ServerHandler::ServerHandler(const char *serverAddr, short serverPort)
{
    m_Socket = BaseSocket();
    m_Socket.init();
    m_Socket.setRemoteAddress(serverAddr, serverPort);
    m_Socket.bindToHost();
}

ServerHandler::~ServerHandler()
{
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

    m_Socket.closeSocket();
}

void ServerHandler::activateConnection()
{
    m_Socket.connectToRemote();
    m_Socket.setNonBlocking(true);

    m_ServerConnectedMutex.lock();
    m_ServerConnected = true;
    m_ServerConnectedMutex.unlock();

    m_RunningMutex.lock();
    m_Running = true;
    m_RunningMutex.unlock();
    m_UpdateThread = std::thread([this] {
        this->update();
    });
}

void ServerHandler::addServerRecvHandler(ServerRecvHandler *srh)
{
    m_ServerRecvHandler.push_back(srh);
}

bool ServerHandler::isServerConnected() const
{
    return m_ServerConnected;
}

void ServerHandler::update()
{
    int len;
    unsigned char buf[1024];

    while(m_Running && m_ServerConnected)
    {
        len = m_Socket.receiveData((char*) &buf, 1024);

        switch (len)
        {
        case -1:
            break;
        case 0:
            std::cout << "Server disconnected!\n";
            m_ServerConnectedMutex.lock();
            m_ServerConnected = false;
            m_ServerConnectedMutex.unlock();
            break;
        case 1: case 2:
            break;
        default:
            printRecvData(buf, len);

            unsigned short dataCode = buf[0];
            dataCode = dataCode << 8;
            dataCode |= buf[1];
            size_t dataLength = (size_t) len - 2;

            for (auto srh : m_ServerRecvHandler)
            {
                if (srh->canHandleData(dataCode, dataLength))
                {
                    srh->recvData(buf, dataLength);
                }
            }

            const char *msg = "Hello, world!";
            send(m_SockFD, msg, 13, 0);
        }
    }
}

void ServerHandler::printRecvData(unsigned char *rawData, int length) const
{
    std::cout << std::hex;
    std::cout << "Receiving message from server:\n";
    std::cout << "    Header: " << (short) rawData[0] << ' ' << (short) rawData[1] << '\n';
    std::cout << "    Data  : ";

    for (int i = 2; i < length; i++)
    {
        if (((i - 2) % 8 == 0) && (i != 2))
        {
            std::cout << "            ";
        }
        std::cout << (short) rawData[i] << ' ';
        if (((i - 1) % 8 == 0) && ((i + 1) != length))
        {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
    std::cout << std::dec;
}
