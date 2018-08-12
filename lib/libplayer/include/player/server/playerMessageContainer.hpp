//
// Created by Brendan Berg on 17.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERMESSAGECONTAINER_HPP
#define NETWORKGAMETEST_PLAYERMESSAGECONTAINER_HPP

#include "player/server/player.hpp"

#include <net/messageContainer.hpp>


/**
 * @brief class that represents a received message and it's source player
 */
class PlayerMessageContainer : public MessageContainer
{

public:

    /**
     * @brief constructor allocates memory for message buffer and initializes all header information
     * @param bufferSize number of bytes for the message buffer
     */
    explicit PlayerMessageContainer(int bufferSize);

    /**
     * @brief set the messages source node
     * @param player source node of the message
     */
    void setPlayer(Player* player);

    /**
     * @brief get the messages source node
     * @return source node of the message
     */
    Player* getPlayer();


private:

    /**
     * @brief source node of the message
     */
    Player* m_Player;


};


#endif //NETWORKGAMETEST_PLAYERMESSAGECONTAINER_HPP
