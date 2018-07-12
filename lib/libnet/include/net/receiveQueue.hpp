//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_RECEIVEQUEUE_HPP
#define NETWORKGAMETEST_RECEIVEQUEUE_HPP

#include "net/messageContainer.hpp"

#include <sock/transmissionSocket.hpp>


// TODO: add TransmissionQueue base class
/**
 * @brief class that represents a queue of received messages and dispatches them into separate message containers
 */
class ReceiveQueue
{

public:

    /**
     * @brief constructor allocates memory for the receive buffer
     * @param bufferSize number of bytes for the receive buffer
     */
    explicit ReceiveQueue(int bufferSize);

    /**
     * @brief destructor deallocates memory used by the receive buffer
     */
    ~ReceiveQueue();

    /**
     * @brief copy newly received bytes into the buffer and reposition the cursor
     * @param socket socket which provides the ability to receive a stream of bytes
     * @return number of received bytes
     * @retval -1 no new data received
     * @retval 0 lost TCP connection
     */
    int receive(TransmissionSocket* socket);

    /**
     * @brief check whether a complete message is available by checking the number of received bytes in the queue
     * @return is a message ready for further processing
     */
    bool messageReadyForProcessing();

    /**
     * @brief dispatch the first message in the queue and copy it's data into the message container
     * @param messageContainer pointer to the target container for the message
     */
    void getMessage(MessageContainer* messageContainer);


private:

    /**
     * @brief pointer to the start of the receive buffer
     */
    char* m_Buffer;

    /**
     * @brief number of bytes for the receive buffer
     */
    int m_BufferSize;

    /**
     * @brief position of the first free byte inside the receive queue
     */
    int m_Cursor;

    /**
     * @brief get the number of free bytes at the end of the receive queue
     * @return free bytes at the end of the receive queue
     */
    int getAvailableBytes();

    /**
     * @brief get the data size of the first message inside the receive queue
     * @return size of the first message inside the receive queue without header information
     * @retval 0 header of first message is not complete
     */
    unsigned short getFirstDataSize();

    /**
     * @brief get the header of the first message inside the receive queue
     * @return header of the first message inside the receive queue
     * @retval 0 header of first message is not complete
     */
    unsigned char getFirstHeader();


};


#endif //NETWORKGAMETEST_RECEIVEQUEUE_HPP
