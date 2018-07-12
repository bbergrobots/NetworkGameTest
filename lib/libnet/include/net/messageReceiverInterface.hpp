//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_MESSAGERECEIVER_HPP
#define NETWORKGAMETEST_MESSAGERECEIVER_HPP

#include "net/messageContainer.hpp"

#include <cstdlib>


/**
 * @brief interface that provides tha ability for a class to process a received network message
 */
class MessageReceiverInterface
{

public:

    /**
     * @brief check whether the implementing class can process the provided network message
     * @param messageContainer pointer to a received network message
     * @return class can or cannot process the provided network message
     *
     * This function should only check whether the message can be processed based on the provided
     * header and length of the message to avoid heavy buffer copying, which can be a bottleneck for
     * the entire network communication pipeline.
     */
    virtual bool canProcessData(MessageContainer* messageContainer) const = 0;

    /**
     * @brief process the received network message
     * @param messageContainer pointer to a received network message
     *
     * This function should be used to copy the message buffer because it is not guaranteed that
     * the data will be available later. Also, the function should just focus on light-weight
     * processing to avoid stopping the network communication pipeline. This can be done e.g. by
     * adding the message to a work queue and take care of it later or in an external thread.
     */
    virtual void processData(MessageContainer* messageContainer) = 0;
};


#endif //NETWORKGAMETEST_MESSAGERECEIVER_HPP
