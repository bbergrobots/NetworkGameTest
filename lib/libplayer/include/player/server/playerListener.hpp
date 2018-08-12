//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERLISTENER_HPP
#define NETWORKGAMETEST_PLAYERLISTENER_HPP

#include "player/server/playerNetworkComponent.hpp"

#include <net/server/serverConnectionController.hpp>


/**
 * @brief class that represents
 */
class PlayerListener
{

public:

    /**
     * @brief constructor initializes the server sided connection handling
     * @param hostPort the port number the listener is assigned to, use 0 for any open port
     */
    explicit PlayerListener(unsigned short hostPort);

    /**
     * @brief check whether new player has connected to the server
     * @return is a new player available?
     */
    bool newPlayerAvailable();

    /**
     * @brief create a new network component when new player has connected
     * @return pointer to new player network component
     * @retval nullptr no new incoming connection
     */
    PlayerNetworkComponent* getNewPlayerNetworkComponent();


private:

    /**
     * @brief handler for incoming server connections
     */
    ServerConnectionController m_ConnectionHandler;


};


#endif //NETWORKGAMETEST_PLAYERLISTENER_HPP
