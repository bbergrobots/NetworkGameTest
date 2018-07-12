//
// Created by Brendan Berg on 12.07.18.
//

#include "player/server/playerCollection.hpp"


PlayerCollection::PlayerCollection(PlayerListener* listener)
    : m_Listener(listener)
{

}

PlayerCollection::~PlayerCollection()
{
    delete m_Listener;
}

void PlayerCollection::update()
{
    if (m_Listener->newPlayerAvailable())
    {
        m_Player.emplace_back(m_Listener->getNewPlayerNetworkComp());
    }

    for (auto it = m_Player.begin(); it != m_Player.end(); it++)
    {
        if (it->isClientConnected())
        {
            it->update();
        }
        else
        {
            m_Player.erase(it);
        }
    }
}
