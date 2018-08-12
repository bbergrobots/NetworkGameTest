//
// Created by Brendan Berg on 12.07.18.
//

#ifndef NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP
#define NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP

#include <sock/sessionSocket.hpp>
#include <net/messageContainer.hpp>
#include <net/receiveQueue.hpp>
#include <net/sendQueue.hpp>


/**
 * @brief class that represents the network component of a player
 */
class PlayerNetworkComponent
{

public:

    /**
     * @brief constructor sets up all transmission queues and buffers
     * @param socket socket connected with player node
     */
    explicit PlayerNetworkComponent(SessionSocket* socket);

    /**
     * @brief destructor deletes the socket
     */
    ~PlayerNetworkComponent();

    /**
     * @brief check whether the client is connected
     * @return is client connected
     */
    bool isClientConnected() const;

    /**
     * @brief get the file descriptor of the associated socket
     * @return file descriptor
     */
    int getFileDescriptor() const;

    /**
     * @brief add message to send queue
     * @param messageContainer message to send in the near future
     */
    void sendMessage(MessageContainer* messageContainer);

    /**
     * @brief work through both transmission queues and check for incoming messages
     */
    void update();


private:

    /**
     * @brief socket connected with player node
     */
    SessionSocket* m_Socket;

    /**
     * @brief flag containing node connectivity state
     */
    bool m_ClientConnected;

    /**
     * @brief buffer for received message
     */
    MessageContainer m_MessageContainer;

    /**
     * @brief queue for received messages
     */
    ReceiveQueue m_ReceiveQueue;

    /**
     * @brief queue for messages to send
     */
    SendQueue m_SendQueue;


};


#endif //NETWORKGAMETEST_PLAYERNETWORKCOMPONENT_HPP
