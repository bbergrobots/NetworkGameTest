//
// Created by Brendan Berg on 09.07.18.
//

#include "sock/listeningSocket.hpp"

#include <cassert>


ListeningSocket::ListeningSocket(short port)
    : BaseSocket()
{
    init();
    bindToHost(port);
    startConnectionListening();
}

SessionSocket* ListeningSocket::acceptConnection()
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

void ListeningSocket::startConnectionListening()
{
    int ret;

    ret = listen(m_SockFD, 8);
    assert(ret != -1);

    setNonBlocking(true);
}
