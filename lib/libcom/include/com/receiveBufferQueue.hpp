//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_RECEIVEBUFFERQUEUE_HPP
#define NETWORKGAMETEST_RECEIVEBUFFERQUEUE_HPP

#include "com/messageContainer.hpp"

#include <sock/transmissionSocket.hpp>


class ReceiveBufferQueue
{

public:

    explicit ReceiveBufferQueue(int bufferSize);

    ~ReceiveBufferQueue();

    int receive(TransmissionSocket* socket);

    bool messageReadyForProcessing();

    void encloseMessage(MessageContainer* messageContainer);


private:

    char* m_Buffer;

    int m_BufferSize;

    int m_Cursor;

    int getAvailableBytes();

    unsigned short getFirstDataSize();

    unsigned char getFirstHeader();


};


#endif //NETWORKGAMETEST_RECEIVEBUFFERQUEUE_HPP
