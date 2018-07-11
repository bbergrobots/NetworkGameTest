//
// Created by Brendan Berg on 11.07.18.
//

#include "plctrl/server/playerController.hpp"


PlayerController::PlayerController(SessionSocket* socket)
    : PlayerConnection(socket)
{
}
