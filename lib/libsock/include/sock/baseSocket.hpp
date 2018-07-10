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

//    void setRemoteAddress(const char* remoteAddress, short remotePort);

    void setNonBlocking(bool state);

    void bindToHost(short port);
//
//    void connectToRemote();
//
//    int receiveData(char* buffer, int length);

    int getFileDescriptor();

    void closeSocket();


protected:

    int m_SockFD;

    struct sockaddr_in m_HostAddress;


};


#endif //NETWORKGAMETEST_BASESOCKET_HPP
