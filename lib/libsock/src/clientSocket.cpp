//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/clientSocket.hpp"

#include <arpa/inet.h>
#include <cassert>


ClientSocket::ClientSocket(const char* serverAddress, unsigned short serverPort)
    : TransmissionSocket()
{
    struct in_addr serverInAddr{};
    inet_aton(serverAddress, &serverInAddr);

    m_ServerAddr.sin_family = AF_INET;
    m_ServerAddr.sin_addr = serverInAddr;
    m_ServerAddr.sin_port = htons(serverPort);

    init();
    bindToHost(0);
}

void ClientSocket::establishConnection() const
{
    auto addr = const_cast<struct sockaddr*>(reinterpret_cast<const struct sockaddr*>(&m_ServerAddr));
    int ret = connect(m_SockFD, addr, sizeof(struct sockaddr));
    assert(ret != -1);

    setNonBlocking(true);
}