//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_SENDQUEUE_HPP
#define NETWORKGAMETEST_SENDQUEUE_HPP

#include "com/messageContainer.hpp"

#include <sock/transmissionSocket.hpp>

#include <mutex>


// TODO: add TransmissionQueue base class
class SendQueue
{

public:

    explicit SendQueue(int bufferSize);

    ~SendQueue();

    int setMessage(MessageContainer* messageContainer);

    bool messageReadyForSending();

    int send(TransmissionSocket* socket);


private:

    char* m_Buffer;

    int m_BufferSize;

    int m_Cursor;

    std::mutex m_Mutex;

    int getAvailableBytes();


};


#endif //NETWORKGAMETEST_SENDQUEUE_HPP
