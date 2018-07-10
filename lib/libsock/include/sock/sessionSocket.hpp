//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_SESSIONSOCKET_HPP
#define NETWORKGAMETEST_SESSIONSOCKET_HPP

#include "sock/transmissionSocket.hpp"


/**
 * @brief class that represents a single socket that got created as a result of a new incoming connection
 */
class SessionSocket : public TransmissionSocket
{

public:

    /**
     * @brief constructor sets information about the system socket and the device that initiated the connection
     * @param sockFieldDescriptor field descriptor of associated system socket
     * @param addr address information about remote host
     */
    SessionSocket(int sockFieldDescriptor, struct sockaddr_in addr);

    /**
     * @brief get a string containing the IPv4 address of the remote host
     * @return string containing the IPv4 address of the remote host
     */
    const char* getClientAddress() const;

    /**
     * @brief get the port number used by the socket on the remote host
     * @return port number of the socket on the remote host
     */
    unsigned short getClientPort() const;


private:

    /**
     * @brief remote address information
     */
    struct sockaddr_in m_ClientAddress;


};


#endif //NETWORKGAMETEST_SESSIONSOCKET_HPP
