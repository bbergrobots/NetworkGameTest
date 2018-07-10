//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/clientSocket.hpp"

#include <arpa/inet.h>
#include <cassert>


ClientSocket::ClientSocket(const char* serverAddr, short serverPort)
    : TransmissionSocket()
{
    struct in_addr serverInAddr{};
    inet_aton(serverAddr, &serverInAddr);

    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr = serverInAddr;
    m_ServerAddr.sin_port = htons(serverPort);

    init();
    bindToHost(0);
}

void ClientSocket::establishConnection()
{
    int ret = connect(m_SockFD, reinterpret_cast<struct sockaddr*>(&m_ServerAddr), sizeof(struct sockaddr));
    assert(ret != -1);

    setNonBlocking(true);
}