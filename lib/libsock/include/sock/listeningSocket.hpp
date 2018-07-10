//
// Created by Brendan Berg on 09.07.18.
//

#ifndef NETWORKGAMETEST_LISTENINGSOCKET_HPP
#define NETWORKGAMETEST_LISTENINGSOCKET_HPP

#include "sock/baseSocket.hpp"
#include "sock/sessionSocket.hpp"


/**
 * @brief class that represents a single socket that is capable of listening for incoming connections
 */
class ListeningSocket : public BaseSocket
{

public:

    /**
     * @brief constructor creates the socket, assigns it to a host port and starts listening for incoming connections
     * @param port the port number the socket is assigned to, use 0 for any open port
     */
    explicit ListeningSocket(short port);

    /**
     * @brief check for new connection and create new session socket associated with incoming system socket
     * @return pointer to new session socket
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
