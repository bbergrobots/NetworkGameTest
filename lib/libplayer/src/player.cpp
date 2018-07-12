//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/player.hpp"

#include <iostream>


Player::Player(PlayerNetworkComponent* networkComponent)
    : m_NetworkComp(networkComponent)
{
    std::cout << "Construct player with file descriptor " << m_NetworkComp->getFileDescriptor() << "\n\n";
}

Player::~Player()
{
    std::cout << "Destruct player with file descriptor " << m_NetworkComp->getFileDescriptor() << "\n\n";
    delete m_NetworkComp;
}

bool Player::isClientConnected()
{
    return m_NetworkComp->isClientConnected();
}

void Player::update()
{
    m_NetworkComp->update();
}
