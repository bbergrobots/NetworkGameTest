//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERCONTROLLER_HPP
#define NETWORKGAMETEST_PLAYERCONTROLLER_HPP

#include "player/server/playerConnection.hpp"


class PlayerController : public PlayerConnection
{

public:

    explicit PlayerController(SessionSocket* socket);


private:


};


#endif //NETWORKGAMETEST_PLAYERCONTROLLER_HPP
