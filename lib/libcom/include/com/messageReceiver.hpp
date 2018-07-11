//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_MESSAGERECEIVER_HPP
#define NETWORKGAMETEST_MESSAGERECEIVER_HPP

#include "com/messageContainer.hpp"

#include <cstdlib>


class MessageReceiver
{

public:

    virtual bool canProcessData(MessageContainer* msg) const = 0;

    virtual void processData(MessageContainer* msg) = 0;
};


#endif //NETWORKGAMETEST_MESSAGERECEIVER_HPP
