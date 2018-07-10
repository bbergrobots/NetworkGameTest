//
// Created by Brendan Berg on 09.07.18.
//

#ifndef NETWORKGAMETEST_LISTENINGSOCKET_HPP
#define NETWORKGAMETEST_LISTENINGSOCKET_HPP

#include "sock/baseSocket.hpp"
#include "sock/sessionSocket.hpp"


class ListeningSocket : public BaseSocket
{

public:

    explicit ListeningSocket(short port);

    SessionSocket* acceptConnection();


private:

    void startConnectionListening();


};


#endif //NETWORKGAMETEST_LISTENINGSOCKET_HPP
