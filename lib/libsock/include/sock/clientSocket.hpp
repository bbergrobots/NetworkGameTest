//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_CLIENTSOCKET_HPP
#define NETWORKGAMETEST_CLIENTSOCKET_HPP

#include "sock/transmissionSocket.hpp"


/**
 * @brief class that represents a single socket that is capable of connecting to a remote host
 */
class ClientSocket : public TransmissionSocket
{

public:

    /**
     * @brief constructor sets information about the targeted remote host and binds the socket to a free host port
     * @param serverAddress string containing the IPv4 address of the targeted remote host
     * @param serverPort targeted port on the remote host
     */
    ClientSocket(const char* serverAddress, unsigned short serverPort);

    /**
     * @brief connect to targeted remote host and set non-blocking mode
     */
    void establishConnection() const;


private:

    /**
     * @brief remote address information
     */
    sockaddr_in m_ServerAddr;


};


#endif //NETWORKGAMETEST_CLIENTSOCKET_HPP
