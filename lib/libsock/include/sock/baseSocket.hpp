//
// Created by Brendan Berg on 22.06.18.
//

#ifndef NETWORKGAMETEST_BASESOCKET_HPP
#define NETWORKGAMETEST_BASESOCKET_HPP

#include <netinet/in.h>


class BaseSocket
{
public:

    BaseSocket();

    ~BaseSocket();

    void init();

    void setHostPort(short port);

    void setRemoteAddress(const char* remoteAddress, short remotePort);

    void setNonBlocking(bool state);

    void bindToHost();

    void listenForConnections();

    int acceptConnection(struct sockaddr* clientAddr);

    void connectToRemote();

    int receiveData(char* buffer, int length);

    void closeSocket();

protected:

    int m_SockFD;

private:


    struct sockaddr_in m_HostAddress;

    struct sockaddr_in m_RemoteAddress;
};


#endif //NETWORKGAMETEST_BASESOCKET_HPP
