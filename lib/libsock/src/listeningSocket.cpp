//
// Created by Brendan Berg on 09.07.18.
//

#include "sock/listeningSocket.hpp"

#include <cassert>


ListeningSocket::ListeningSocket(short hostPort)
    : BaseSocket()
{
    init();
    bindToHost(hostPort);
    startConnectionListening();
}

SessionSocket* ListeningSocket::acceptConnection() const
{
    struct sockaddr_in clientAddr{};
    socklen_t sockInSize = sizeof(struct sockaddr_in);

    int newSockFD = accept(m_SockFD, reinterpret_cast<struct sockaddr*>(&clientAddr), &sockInSize);

    if (newSockFD == -1)
    {
        return nullptr;
    }
    else
    {
        auto newSock = new SessionSocket(newSockFD, clientAddr);
        return newSock;
    }
}

void ListeningSocket::startConnectionListening() const
{
    int ret;

    ret = listen(m_SockFD, 8);
    assert(ret != -1);

    setNonBlocking(true);
}
