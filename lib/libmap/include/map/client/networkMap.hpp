//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_NETWORKMAP_HPP
#define NETWORKGAMETEST_NETWORKMAP_HPP

#include "map/baseMap.hpp"

#include <net/messageReceiverInterface.hpp>


/**
 * @brief class that represents the game map which gets loaded through the network pipeline
 */
class NetworkMap : public BaseMap, public MessageReceiverInterface
{

public:

    /**
     * @brief constructor calls the superclass' constructor
     * @param size number of 8x8 chunks per dimension
     */
    explicit NetworkMap(unsigned int size);

    /**
     * @brief implemented function checks whether the class can process the provided network message
     * @param messageContainer pointer to a received network message
     * @return class can or cannot process the provided network message
     */
    bool canProcessData(MessageContainer* messageContainer) const override;

    /**
     * @brief process the received network message
     * @param messageContainer pointer to a received network message
     */
    void processData(MessageContainer* messageContainer) override;
};


#endif //NETWORKGAMETEST_NETWORKMAP_HPP
