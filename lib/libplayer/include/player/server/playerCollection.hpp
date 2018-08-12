//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERCOLLECTION_HPP
#define NETWORKGAMETEST_PLAYERCOLLECTION_HPP

#include "player/server/playerListener.hpp"
#include "player/server/player.hpp"
#include "player/server/playerMessageContainer.hpp"

#include <net/messageReceiverInterface.hpp>

#include <list>


/**
 * @brief class that represents the set of all active players
 */
class PlayerCollection
{

public:

    /**
     * @brief constructor assigned itself to the player listener
     * @param listener listener for incoming player connections
     */
    explicit PlayerCollection(PlayerListener* listener);

    /**
     * @brief destructor deletes player listener
     */
    ~PlayerCollection();

    /**
     * @brief register a new object as a message receiver
     * @param messageReceiver new message receiver object
     */
    void registerMessageReceiver(MessageReceiverInterface<PlayerMessageContainer>* messageReceiver);

    /**
     * @brief manage set of connected players
     */
    void update();

private:

    /**
     * @brief listener for incoming player connections
     */
    PlayerListener* m_Listener;

    /**
     * @brief set of connected players
     */
    std::list<Player> m_Player;

    // TODO: accelerate with phone book principle
    /**
     * @brief list of registered message receiver objects
     */
    std::list<MessageReceiverInterface<PlayerMessageContainer>*> m_MessageReceiver;

    /**
     * @brief send empty message body to all message receivers to indicate new connected player
     * @param player pointer to new connected player
     */
    void broadcastMessageOfNewPlayerConnection(Player* player);
};


#endif //NETWORKGAMETEST_PLAYERCOLLECTION_HPP
