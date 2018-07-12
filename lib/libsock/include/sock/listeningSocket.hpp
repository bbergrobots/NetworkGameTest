//
// Created by Brendan Berg on 09.07.18.
//

#ifndef NETWORKGAMETEST_LISTENINGSOCKET_HPP
#define NETWORKGAMETEST_LISTENINGSOCKET_HPP

#include "sock/baseSocket.hpp"
#include "sock/sessionSocket.hpp"


/**
 * @brief class that represents a single socket with the ability to listen for incoming connections
 */
class ListeningSocket : public BaseSocket
{

public:

    /**
     * @brief constructor creates the socket, assigns it to a host port and starts listening for incoming connections
     * @param hostPort the port number the socket is assigned to, use 0 for any open port
     */
    explicit ListeningSocket(short hostPort);

    /**
     * @brief check for new connection and create new session socket associated to the incoming system socket if needed
     * @return pointer to new session socket, user is required to free the pointer after usage
     * @retval nullptr no new incoming connection
     */
    SessionSocket* acceptConnection() const;


private:

    /**
     * @brief start listening for incoming connections and set non-blocking mode
     */
    void startConnectionListening() const;


};


#endif //NETWORKGAMETEST_LISTENINGSOCKET_HPP
