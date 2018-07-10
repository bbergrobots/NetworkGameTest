//
// Created by Brendan Berg on 22.06.18.
//

#ifndef NETWORKGAMETEST_BASESOCKET_HPP
#define NETWORKGAMETEST_BASESOCKET_HPP

#include <netinet/in.h>


/**
 * @brief class that represents a single socket with basic functionality
 */
class BaseSocket
{

public:

    /**
     * @brief constructor initializes attributes without specializing socket operations
     */
    BaseSocket();

    /**
     * @brief destructor closes the socket if open
     */
    ~BaseSocket();

    /**
     * @brief perform system calls to create the socket
     *
     * This function should not get used for sockets created by the listening for incoming connections.
     */
    void init();

    /**
     * @brief set blocking option for socket
     * @param state state of non-blocking flag
     *
     * This function should not get used for sockets created by the listening for incoming connections.
     */
    void setNonBlocking(bool state) const;

    /**
     * @brief bind socket to host
     * @param port the port number the socket is assigned to, use 0 for any open port
     *
     * This function should not get used for sockets created by the listening for incoming connections.
     */
    void bindToHost(short port);

    /**
     * @brief get the file descriptor of the socket for debugging purposes
     * @return the file descriptor
     */
    int getFileDescriptor() const;

    /**
     * @brief close the socket if open
     */
    void closeSocket() const;


protected:

    /**
     * @brief file descriptor of the associated system socket
     */
    int m_SockFD;

    /**
     * @brief host address information
     */
    struct sockaddr_in m_HostAddress;


};


#endif //NETWORKGAMETEST_BASESOCKET_HPP
