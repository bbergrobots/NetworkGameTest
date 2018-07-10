//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_NETWORKMAP_HPP
#define NETWORKGAMETEST_NETWORKMAP_HPP

#include "map/baseMap.hpp"

#include <scom/client/serverMessageReceiver.hpp>


class NetworkMap : public BaseMap, public ServerMessageReceiver
{

public:

    explicit NetworkMap(unsigned int size);

    bool canProcessData(unsigned short header, int length) const override;

    void processData(void* rawData, int length) override;
};


#endif //NETWORKGAMETEST_NETWORKMAP_HPP
