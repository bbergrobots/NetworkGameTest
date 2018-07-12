//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYER_HPP
#define NETWORKGAMETEST_PLAYER_HPP

#include "player/server/playerNetworkComponent.hpp"


class Player
{

public:

    explicit Player(PlayerNetworkComponent* networkComponent);

    ~Player();

    bool isClientConnected();

    void update();


private:

    PlayerNetworkComponent* m_NetworkComp;


};


#endif //NETWORKGAMETEST_PLAYER_HPP
