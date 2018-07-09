//
// Created by Brendan Berg on 09.07.18.
//

#include "sock/listeningSocket.hpp"


ListeningSocket::ListeningSocket(short port)
    : BaseSocket()
{
    init();
    setHostPort(port);
    bindToHost();
    listenForConnections();
    setNonBlocking(true);
}

SessionSocket* ListeningSocket::acceptConnection()
{
    struct sockaddr_in clientAddr{};
    int newSockFD = BaseSocket::acceptConnection(reinterpret_cast<struct sockaddr*>(&clientAddr));

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
