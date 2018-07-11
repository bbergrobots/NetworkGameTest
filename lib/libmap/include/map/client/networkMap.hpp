//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_NETWORKMAP_HPP
#define NETWORKGAMETEST_NETWORKMAP_HPP

#include "map/baseMap.hpp"

#include <com/messageReceiverInterface.hpp>


class NetworkMap : public BaseMap, public MessageReceiverInterface
{

public:

    explicit NetworkMap(unsigned int size);

    bool canProcessData(MessageContainer* msg) const override;

    void processData(MessageContainer* msg) override;
};


#endif //NETWORKGAMETEST_NETWORKMAP_HPP
