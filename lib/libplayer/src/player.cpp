//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/player.hpp"

#include <iostream>


Player::Player(PlayerNetworkComponent* networkComponent)
    : m_NetworkComponent(networkComponent)
{
    std::cout << "Construct player with file descriptor " << m_NetworkComponent->getFileDescriptor() << "\n\n";
}

Player::~Player()
{
    std::cout << "Destruct player with file descriptor " << m_NetworkComponent->getFileDescriptor() << "\n\n";
    delete m_NetworkComponent;
}

PlayerNetworkComponent* Player::getNetworkComponent() const
{
    return m_NetworkComponent;
}

void Player::update()
{
    m_NetworkComponent->update();
}
