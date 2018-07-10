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
    std::cout << "Constructing player with FD " << m_Socket->getFileDescriptor() << ".\n";
    std::cout << "    Address : " << m_Socket->getClientAddress() << "\n";
    std::cout << "    Port    : " << m_Socket->getClientPort() << "\n";

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
    std::cout << "Destructing player with FD " << m_Socket->getFileDescriptor() << ".\n";

    // deactivate update thread
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

    delete m_Socket;
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
        len = m_Socket->receiveData(&buf[0], 1024);

        switch (len)
        {
        case -1:
            break;
        case 0:
            std::cout << "Client with FD " << m_Socket->getFileDescriptor() << " disconnected.\n";
            m_ClientConnectedMutex.lock();
            m_ClientConnected = false;
            m_ClientConnectedMutex.unlock();
            break;
        default:
            std::cout << "Receiving message from player with FD " << m_Socket->getFileDescriptor() << ":\n    ";
            for(ssize_t i = 0; i < len; i++)
            {
                std::cout << buf[i];
            }
            std::cout << '\n';
        }
    }
}

void Player::sendRawData(unsigned char* data, int length) const
{
    m_Socket->sendData(reinterpret_cast<char*>(data), length);
}

void Player::sendMap(unsigned char* mapData) const
{
    auto data = new unsigned char[16 * 2 + 2];
    memcpy(data + 2, mapData, 16 * 2);
    memset(data, 0x00, 2);
    data[0] = 0x10;

    sendRawData(data, 16 * 2 + 2);
}
