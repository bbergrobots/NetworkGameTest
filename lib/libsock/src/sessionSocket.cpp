//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/sessionSocket.hpp"

#include <arpa/inet.h>


SessionSocket::SessionSocket(int socketFieldDescriptor, struct sockaddr_in clientAddress)
    : TransmissionSocket(), m_ClientAddress(clientAddress)
{
    m_SockFD = socketFieldDescriptor;
}

const char* SessionSocket::getClientAddress() const
{
    return inet_ntoa(m_ClientAddress.sin_addr);
}

unsigned short SessionSocket::getClientPort() const
{
    return ntohs(m_ClientAddress.sin_port);
}
