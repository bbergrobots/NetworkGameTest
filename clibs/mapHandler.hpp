//
// Created by Brendan Berg on 16.06.18.
//

#ifndef NETWORKGAMETEST_MAPHANDLER_HPP
#define NETWORKGAMETEST_MAPHANDLER_HPP


#include "serverRecvHandler.hpp"


class MapHandler : public ServerRecvHandler
{
public:

    MapHandler();

    ~MapHandler();

    bool canHandleData(unsigned short dataCode, size_t length) const override;

    void recvData(unsigned char* rawData, size_t length) override;

    void recvMap(unsigned char* rawData);

    void print() const;


private:

    unsigned char* m_Map;

};


#endif //NETWORKGAMETEST_MAPHANDLER_HPP
