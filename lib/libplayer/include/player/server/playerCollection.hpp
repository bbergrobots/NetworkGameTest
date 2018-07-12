//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERCOLLECTION_HPP
#define NETWORKGAMETEST_PLAYERCOLLECTION_HPP

#include "player/server/playerListener.hpp"

#include "player/server/player.hpp"

#include <list>


class PlayerCollection
{

public:

    // TODO: provide with listener instead of hostPort
    explicit PlayerCollection(PlayerListener* listener);

    ~PlayerCollection();

    void update();

private:

    PlayerListener* m_Listener;

    std::list<Player> m_Player;
};


#endif //NETWORKGAMETEST_PLAYERCOLLECTION_HPP
