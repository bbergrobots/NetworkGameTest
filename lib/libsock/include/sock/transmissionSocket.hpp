//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP
#define NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP

#include "sock/baseSocket.hpp"


/**
 * @brief class that represents a single socket with the functionality of transmitting data
 */
class TransmissionSocket : public BaseSocket
{

public:

    /**
     * @brief copy received data into buffer
     * @param buffer destination for received data
     * @param length size of destination buffer
     * @return received number of bytes
     * @retval -1 no new data received
     * @retval 0 lost TCP connection
     */
    int receiveData(void* buffer, int length) const;

    /**
     * @brief send data inside buffer via socket
     * @param buffer source of bytes to send
     * @param length number of bytes to send
     * @return number of bytes sent
     * @retval -1 an error occurred
     */
    int sendData(const void* buffer, int length) const;


};


#endif //NETWORKGAMETEST_TRANSMISSIONSOCKET_HPP
