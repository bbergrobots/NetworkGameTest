//
// Created by Brendan Berg on 10.06.18.
//

#include "player.hpp"

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


Player::Player(int sockFD, struct sockaddr_in clientAddr)
    : m_SockFD(sockFD), m_ClientAddr(clientAddr)
{
    std::cout << "Constructing player with FD " << m_SockFD << ".\n";
    std::cout << "    Address : " << inet_ntoa(m_ClientAddr.sin_addr) << "\n";
    std::cout << "    Port    : " << ntohs(m_ClientAddr.sin_port) << "\n";

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
    std::cout << "Destructing player with FD " << m_SockFD << ".\n";

    // deactivate update thread
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

    close(m_SockFD);
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
        len = recv(m_SockFD, &buf, 1024, 0);

        switch (len)
        {
        case -1:
            break;
        case 0:
            std::cout << "Client with FD " << m_SockFD << " disconnected.\n";
            m_ClientConnectedMutex.lock();
            m_ClientConnected = false;
            m_ClientConnectedMutex.unlock();
            break;
        default:
            std::cout << "Receiving message from player with FD " << m_SockFD <<":\n    ";
            for(ssize_t i = 0; i < len; i++)
            {
                std::cout << (char) buf[i];
            }
            std::cout << '\n';
        }
    }
}

void Player::sendMap(char* mapData) const
{
    send(m_SockFD, mapData, 16 * 2, 0);
}
