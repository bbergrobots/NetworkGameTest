//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SERVERMESSAGERECEIVER_HPP
#define NETWORKGAMETEST_SERVERMESSAGERECEIVER_HPP

#include <cstdlib>


class ServerMessageReceiver
{

public:

    virtual bool canProcessData(unsigned short header, int length) const = 0;

    virtual void processData(void* rawData, int length) = 0;
};


#endif //NETWORKGAMETEST_SERVERMESSAGERECEIVER_HPP
