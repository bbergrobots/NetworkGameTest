//
// Created by Brendan Berg on 10.06.18.
//

#include "player.hpp"

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


Player::Player(SessionSocket* socket)
    : m_Socket(socket)
{
    std::cout << "Constructing player with FD " << ".\n";
//    std::cout << "    Address : " << inet_ntoa(m_ClientAddr.sin_addr) << "\n";
//    std::cout << "    Port    : " << ntohs(m_ClientAddr.sin_port) << "\n";

    m_ClientConnectedMutex.lock();
    m_ClientConnected = true;
    m_ClientConnectedMutex.unlock();

    // start update thread
    m_RunningMutex.lock();
    m_Running = true;
    m_RunningMutex.unlock();
    m_UpdateThread = std::thread([this] {
        this->update();
    });
}

Player::~Player()
{
    std::cout << "Destructing player with FD " << ".\n";

    // deactivate update thread
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

//    close(m_SockFD);
    m_Socket->closeSocket();
}

bool Player::isClientConnected() const
{
    return m_ClientConnected;
}

void Player::update()
{
    ssize_t len;
    char buf[1024];

    while(m_Running && m_ClientConnected)
    {
//        len = recv(m_SockFD, &buf, 1024, 0);
        len = m_Socket->receiveData(&buf[0], 1024);

        switch (len)
        {
        case -1:
            break;
        case 0:
            std::cout << "Client with FD " << " disconnected.\n";
            m_ClientConnectedMutex.lock();
            m_ClientConnected = false;
            m_ClientConnectedMutex.unlock();
            break;
        default:
            std::cout << "Receiving message from player with FD " <<":\n    ";
            for(ssize_t i = 0; i < len; i++)
            {
                std::cout << buf[i];
            }
            std::cout << '\n';
        }
    }
}

void Player::sendRawData(unsigned char *data, size_t length) const
{
//    send(m_SockFD, data, length, 0);
    send(m_Socket->getFD(), data, length, 0);
}

void Player::sendMap(unsigned char* mapData) const
{
    auto data = new unsigned char[16 * 2 + 2];
    memcpy(data + 2, mapData, 16 * 2);
    memset(data, 0x00, 2);
    data[0] = 0x10;

    sendRawData(data, 16 * 2 + 2);
}
