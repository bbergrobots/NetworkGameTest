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

void PlayerCollection::registerMessageReceiver(MessageReceiverInterface<PlayerMessageContainer>* messageReceiver)
{
    m_MessageReceiver.push_back(messageReceiver);
}

void PlayerCollection::update()
{
    if (m_Listener->newPlayerAvailable())
    {
        m_Player.emplace_back(m_Listener->getNewPlayerNetworkComponent());
        broadcastMessageOfNewPlayerConnection(&(m_Player.back()));
    }

    for (auto it = m_Player.begin(); it != m_Player.end(); it++)
    {
        if (it->getNetworkComponent()->isClientConnected())
        {
            it->update();
        }
        else
        {
            m_Player.erase(it);
        }
    }
}

void PlayerCollection::broadcastMessageOfNewPlayerConnection(Player* player)
{
    PlayerMessageContainer msg(0);
    msg.setDataSize(0);
    msg.setHeader(0x00);
    msg.setPlayer(player);

    for (auto i : m_MessageReceiver)
    {
        if (i->canProcessData(&msg))
        {
            i->processData(&msg);
        }
    }
}
