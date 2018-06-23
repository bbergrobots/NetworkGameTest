//
// Created by Brendan Berg on 22.06.18.
//

#ifndef NETWORKGAMETEST_SERVERRECVHANDLER_HPP
#define NETWORKGAMETEST_SERVERRECVHANDLER_HPP


#include <cstdlib>


class ServerRecvHandler
{
public:

    virtual bool canHandleData(unsigned short dataCode, size_t length) const = 0;

    virtual void recvData(unsigned char* rawData, size_t length) = 0;

};


#endif //NETWORKGAMETEST_SERVERRECVHANDLER_HPP
