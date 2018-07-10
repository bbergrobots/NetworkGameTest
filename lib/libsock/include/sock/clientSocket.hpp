//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_CLIENTSOCKET_HPP
#define NETWORKGAMETEST_CLIENTSOCKET_HPP

#include "sock/transmissionSocket.hpp"


class ClientSocket : public TransmissionSocket
{

public:

    ClientSocket(const char* serverAddr, short serverPort);

    void establishConnection();


private:

    sockaddr_in m_ServerAddr;


};


#endif //NETWORKGAMETEST_CLIENTSOCKET_HPP
