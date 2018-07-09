//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SESSIONSOCKET_HPP
#define NETWORKGAMETEST_SESSIONSOCKET_HPP

#include "sock/baseSocket.hpp"


class SessionSocket : public BaseSocket
{

public:

    SessionSocket(int sockFD, struct sockaddr_in addr);

    int getFD()
    {
        return m_SockFD;
    }


private:

    struct sockaddr_in m_ClientAddress;


};


#endif //NETWORKGAMETEST_SESSIONSOCKET_HPP
