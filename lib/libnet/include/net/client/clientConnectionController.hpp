//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_CLIENTCONNECTIONCONTROLLER_HPP
#define NETWORKGAMETEST_CLIENTCONNECTIONCONTROLLER_HPP

#include "net/messageReceiverInterface.hpp"
#include "net/messageContainer.hpp"

#include <sock/clientSocket.hpp>

#include <list>
#include <thread>


/**
 * @brief class that manages a client sided socket connection
 */
class ClientConnectionController
{

public:

    /**
     * @brief constructor sets up the socket connection to the server
     * @param serverAddress string containing the IPv4 address of the targeted server
     * @param serverPort targeted port on the server
     */
    ClientConnectionController(const char* serverAddress, unsigned short serverPort);

    /**
     * @brief destructor joins the update thread
     */
    ~ClientConnectionController();

    // TODO: accelerate with phone book principle
    /**
     * @brief register an object as a possible receiver for a message
     * @param messageReceiver object to register
     */
    void registerMessageReceiver(MessageReceiverInterface<MessageContainer>* messageReceiver);

    /**
     * @brief establish the socket connection and start the update thread
     *
     * This function should get called after all registrations from message receivers are
     * done. Otherwise messages will get lost / not delivered.
     */
    void establishConnection();

    /**
     * @brief checks whether the server is still connected
     * @return is the server connected
     */
    bool isServerConnected() const;


private:

    /**
     * @brief socket to use for the communication
     */
    ClientSocket m_Socket;

    /**
     * @brief thread that handles all receiving and sending actions to outsource the network bottleneck
     */
    std::thread m_UpdateThread;

    /**
     * @brief flag to notify the update thread to end up its activities
     */
    bool m_Running;

    /**
     * @brief flag used by the update thread to store whether the server is still connected
     */
    bool m_ServerConnected;

    /**
     * @brief list of all objects that can process some kind off received messages
     */
    std::list<MessageReceiverInterface<MessageContainer>*> m_MessageReceiver;

    /**
     * @brief function that runs inside the update thread
     */
    void update();


};


#endif //NETWORKGAMETEST_CLIENTCONNECTIONCONTROLLER_HPP
