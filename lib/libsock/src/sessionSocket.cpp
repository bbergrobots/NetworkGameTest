//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/sessionSocket.hpp"


SessionSocket::SessionSocket(int sockFD, struct sockaddr_in addr)
    : BaseSocket(), m_ClientAddress(addr)
{
    m_SockFD = sockFD;
}
