//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_SENDQUEUE_HPP
#define NETWORKGAMETEST_SENDQUEUE_HPP

#include "net/messageContainer.hpp"

#include <sock/transmissionSocket.hpp>

#include <mutex>


// TODO: add TransmissionQueue base class
/**
 * @brief class that represents a queue of bytes to send via sockets provided by message containers
 */
class SendQueue
{

public:

    /**
     * @brief constructor allocates memory for the send buffer
     * @param bufferSize number of bytes for the send buffer
     */
    explicit SendQueue(int bufferSize);

    /**
     * @brief destructor deallocates memory used by the receive buffer
     */
    ~SendQueue();

    /**
     * @brief add another message contained in a message container to the queue
     * @param messageContainer pointer to the container of the message
     * @return was the appending successful
     */
    bool setMessage(MessageContainer* messageContainer);

    /**
     * @brief check whether the queue contains at least one message
     * @return is there a message in the queue
     */
    bool messageReadyForSending() const;

    /**
     * @brief send all bytes in the queue via the provided socket
     * @param socket socket which provides the ability to send a stream of bytes
     * @return number of sent bytes
     * @retval -1 an error occurred
     */
    int send(TransmissionSocket* socket);


private:

    /**
     * @brief pointer to the start of the send buffer
     */
    char* m_Buffer;

    /**
     * @brief number of bytes for the receive buffer
     */
    int m_BufferSize;

    /**
     * @brief position of the first free byte inside the send queue
     */
    int m_Cursor;

    /**
     * @brief mutex to lock the buffer to make the whole class thread safe
     */
    std::mutex m_Mutex;

    /**
     * @brief get the number of free bytes at the end of the receive queue
     * @return free bytes at the end of the receive queue
     */
    int getAvailableBytes() const;


};


#endif //NETWORKGAMETEST_SENDQUEUE_HPP
