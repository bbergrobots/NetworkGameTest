//
// Created by Brendan Berg on 17.07.18.
//

#include "player/server/playerMessageContainer.hpp"


PlayerMessageContainer::PlayerMessageContainer(int bufferSize)
    : MessageContainer(bufferSize)
{
    m_Player = nullptr;
}

void PlayerMessageContainer::setPlayer(Player* player)
{
    m_Player = player;
}

Player* PlayerMessageContainer::getPlayer()
{
    return m_Player;
}
