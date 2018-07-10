//
// Created by Brendan Berg on 22.06.18.
//

#include "sock/baseSocket.hpp"

#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cassert>
#include <cstring>


BaseSocket::BaseSocket()
{
    m_SockFD = -1;

    m_HostAddress.sin_family = AF_INET;
    m_HostAddress.sin_addr.s_addr = 0;
    m_HostAddress.sin_port = 0;
    memset(&(m_HostAddress.sin_zero), '\0', 8);
}

BaseSocket::~BaseSocket()
{
    closeSocket();
}

void BaseSocket::init()
{
    m_SockFD = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_SockFD != -1);

    int yes = 1;
    int ret = setsockopt(m_SockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    assert(ret != -1);
}

//void BaseSocket::setHostPort(short port)
//{
//    m_HostAddress.sin_port = htons(port);
//}
//
//void BaseSocket::setRemoteAddress(const char *remoteAddress, short remotePort)
//{
//    struct in_addr remoteInAddr{};
//    inet_aton(remoteAddress, &remoteInAddr); // can fail --> returns 0
//    m_RemoteAddress.sin_addr = remoteInAddr;
//    m_RemoteAddress.sin_port = htons(remotePort);
//}

void BaseSocket::setNonBlocking(bool state)
{
    int tmp;

    tmp = fcntl(m_SockFD, F_GETFL);
    if (state)
    {
        tmp |= O_NONBLOCK;
    }
    else
    {
        tmp &= ~O_NONBLOCK;
    }
    fcntl(m_SockFD, F_SETFL, tmp);
}

void BaseSocket::bindToHost(short port)
{
    m_HostAddress.sin_port = htons(port);

    int ret = bind(m_SockFD, reinterpret_cast<struct sockaddr *>(&m_HostAddress), sizeof(struct sockaddr));
    assert(ret != -1);
}

//void BaseSocket::connectToRemote()
//{
//    int ret;
//
//    ret = connect(m_SockFD, reinterpret_cast<struct sockaddr *>(&m_RemoteAddress), sizeof(struct sockaddr));
//    assert(ret != -1);
//}
//
//int BaseSocket::receiveData(char *buffer, int length)
//{
//
//    return static_cast<int>(recv(m_SockFD, buffer, (size_t) length, 0));
//}

int BaseSocket::getFileDescriptor()
{
    return m_SockFD;
}

void BaseSocket::closeSocket()
{
    close(m_SockFD);
}
