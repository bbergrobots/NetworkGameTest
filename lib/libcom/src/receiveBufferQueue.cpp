//
// Created by Brendan Berg on 11.07.18.
//

#include "com/receiveBufferQueue.hpp"

#include <cassert>
#include <cstring>


ReceiveBufferQueue::ReceiveBufferQueue(int bufferSize)
    : m_BufferSize(bufferSize)
{
    m_Buffer = new char[m_BufferSize];
    memset(m_Buffer, 0, static_cast<size_t>(m_BufferSize));
    m_Cursor = 0;
}

ReceiveBufferQueue::~ReceiveBufferQueue()
{
    delete m_Buffer;
}

int ReceiveBufferQueue::receive(TransmissionSocket* socket)
{
    int availableBytes = getAvailableBytes();
    int receivedBytes = socket->receiveData(m_Buffer + m_Cursor, availableBytes);

    if (receivedBytes > 0)
    {
        m_Cursor += receivedBytes;
        assert(m_Cursor < m_BufferSize);
    }

    return receivedBytes;
}

bool ReceiveBufferQueue::messageReadyForProcessing()
{
    unsigned short messageSize = getFirstDataSize();

    return ((m_Cursor >= messageSize + 3) && (messageSize != 0));
}

void ReceiveBufferQueue::encloseMessage(MessageContainer* messageContainer)
{
    if (messageReadyForProcessing())
    {
        unsigned short dataSize = getFirstDataSize();

        // copy data to message container
        messageContainer->setDataSize(dataSize);
        messageContainer->setHeader(getFirstHeader());
        memcpy(messageContainer->getBufferStart(), m_Buffer + 3, dataSize);

        // remove message from queue
        memcpy(m_Buffer, m_Buffer + dataSize + 3, static_cast<size_t>(m_Cursor - (dataSize + 3)));

        // set cursor position
        m_Cursor = m_Cursor - (dataSize + 3);
    }
}

int ReceiveBufferQueue::getAvailableBytes()
{
    return m_BufferSize - m_Cursor;
}

unsigned short ReceiveBufferQueue::getFirstDataSize()
{
    unsigned short size;

    if (m_Cursor < 2)
    {
        size = 0;
    }
    else
    {
        size = static_cast<unsigned short>(m_Buffer[0]);
        size = size << 8u;
        size |= static_cast<unsigned short>(m_Buffer[1]);
    }

    return size;
}

unsigned char ReceiveBufferQueue::getFirstHeader()
{
    return static_cast<unsigned char>(m_Buffer[2]);
}
