//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SESSIONSOCKET_HPP
#define NETWORKGAMETEST_SESSIONSOCKET_HPP

#include "sock/transmissionSocket.hpp"


class SessionSocket : public TransmissionSocket
{

public:

    SessionSocket(int sockFD, struct sockaddr_in addr);

    const char* getClientAddress();

    unsigned short getClientPort();


private:

    struct sockaddr_in m_ClientAddress;


};


#endif //NETWORKGAMETEST_SESSIONSOCKET_HPP
