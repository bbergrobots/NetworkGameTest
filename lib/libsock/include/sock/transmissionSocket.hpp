//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP
#define NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP

#include "sock/baseSocket.hpp"


class TransmissionSocket : public BaseSocket
{

public:

    TransmissionSocket();

    int receiveDate(char* buffer, int length);

    int sendData(char* buffer, int length);


};


#endif //NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP
