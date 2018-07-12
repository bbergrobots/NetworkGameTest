//
// Created by Brendan Berg on 11.07.18.
//

#include "player/server/playerController.hpp"


PlayerController::PlayerController(SessionSocket* socket)
    : PlayerConnection(socket)
{
}
