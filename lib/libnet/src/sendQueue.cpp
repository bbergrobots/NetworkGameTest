//
// Created by Brendan Berg on 11.07.18.
//

#include "net/sendQueue.hpp"


SendQueue::SendQueue(int bufferSize)
    : m_BufferSize(bufferSize)
{
    m_Buffer = new char[m_BufferSize];
    memset(m_Buffer, 0, static_cast<size_t>(m_BufferSize));
    m_Cursor = 0;
}

SendQueue::~SendQueue()
{
    delete m_Buffer;
}

bool SendQueue::setMessage(MessageContainer* messageContainer)
{
    unsigned short messageSize = messageContainer->getDataSize();
    m_Mutex.lock();
    if (getAvailableBytes() > messageSize + 3)
    {

        m_Buffer[m_Cursor + 0] = static_cast<char>(messageSize >> 8u);
        m_Buffer[m_Cursor + 1] = static_cast<char>(messageSize & 0xffu);
        m_Buffer[m_Cursor + 2] = static_cast<char>(messageContainer->getHeader());
        memcpy(m_Buffer + m_Cursor + 3, messageContainer->getBufferStart(), static_cast<size_t>(messageSize));
        m_Cursor = m_Cursor + messageSize + 3;

        m_Mutex.unlock();
        return true;
    }
    else
    {
        m_Mutex.unlock();
        return false;
    }
}

bool SendQueue::messageReadyForSending() const
{
    return m_Cursor != 0;
}

int SendQueue::send(TransmissionSocket* socket)
{
    m_Mutex.lock();
    int ret = socket->sendData(m_Buffer, m_Cursor);
    m_Cursor = 0;
    m_Mutex.unlock();

    return ret;
}

int SendQueue::getAvailableBytes() const
{
    return m_BufferSize - m_Cursor;
}
