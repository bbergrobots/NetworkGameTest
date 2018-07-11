//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_RECEIVEQUEUE_HPP
#define NETWORKGAMETEST_RECEIVEQUEUE_HPP

#include "com/messageContainer.hpp"

#include <sock/transmissionSocket.hpp>


// TODO: add TransmissionQueue base class
class ReceiveQueue
{

public:

    explicit ReceiveQueue(int bufferSize);

    ~ReceiveQueue();

    int receive(TransmissionSocket* socket);

    bool messageReadyForProcessing();

    void getMessage(MessageContainer* messageContainer);


private:

    char* m_Buffer;

    int m_BufferSize;

    int m_Cursor;

    int getAvailableBytes();

    unsigned short getFirstDataSize();

    unsigned char getFirstHeader();


};


#endif //NETWORKGAMETEST_RECEIVEQUEUE_HPP
