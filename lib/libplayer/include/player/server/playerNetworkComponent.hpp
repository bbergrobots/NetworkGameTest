//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP
#define NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP

#include <sock/sessionSocket.hpp>
#include <net/messageContainer.hpp>
#include <net/receiveQueue.hpp>


class PlayerNetworkComponent
{

public:

    explicit PlayerNetworkComponent(SessionSocket* socket);

    ~PlayerNetworkComponent();

    bool isClientConnected();

    int getFileDescriptor();

    void update();


private:

    SessionSocket* m_Socket;

    bool m_ClientConnected;

    MessageContainer m_MessageContainer;

    ReceiveQueue m_ReceiveQueue;

};


#endif //NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP
