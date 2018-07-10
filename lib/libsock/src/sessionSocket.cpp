//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/sessionSocket.hpp"

#include <arpa/inet.h>


SessionSocket::SessionSocket(int sockFD, struct sockaddr_in addr)
    : TransmissionSocket(), m_ClientAddress(addr)
{
    m_SockFD = sockFD;
}

const char* SessionSocket::getClientAddress()
{
    return inet_ntoa(m_ClientAddress.sin_addr);
}

unsigned short SessionSocket::getClientPort()
{
    return ntohs(m_ClientAddress.sin_port);
}
