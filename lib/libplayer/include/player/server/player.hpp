//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYER_HPP
#define NETWORKGAMETEST_PLAYER_HPP

#include "player/server/playerNetworkComponent.hpp"


/**
 * @brief class that represents all components of an active player
 */
class Player
{

public:

    /**
     * @brief constructor calls constructors of all components
     * @param networkComponent network component of the player
     */
    explicit Player(PlayerNetworkComponent* networkComponent);

    /**
     * @brief destructor calls destructors of all components
     */
    ~Player();

    /**
     * @brief get the current network component of the player
     * @return network component
     */
    PlayerNetworkComponent* getNetworkComponent() const;

    /**
     * @brief call update functions of all components
     */
    void update();


private:

    /**
     * @brief network component of the player
     */
    PlayerNetworkComponent* m_NetworkComponent;


};


#endif //NETWORKGAMETEST_PLAYER_HPP
