//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERLISTENER_HPP
#define NETWORKGAMETEST_PLAYERLISTENER_HPP

#include "player/server/playerNetworkComponent.hpp"

#include <net/server/serverConnectionController.hpp>


class PlayerListener
{

public:

    explicit PlayerListener(unsigned short hostPort);

    bool newPlayerAvailable();

    PlayerNetworkComponent* getNewPlayerNetworkComp();


private:

    ServerConnectionController m_ConnectionHandler;


};


#endif //NETWORKGAMETEST_PLAYERLISTENER_HPP
