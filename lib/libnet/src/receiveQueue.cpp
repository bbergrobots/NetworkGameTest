//
// Created by Brendan Berg on 11.07.18.
//

#include "net/receiveQueue.hpp"

#include <cassert>
#include <cstring>


ReceiveQueue::ReceiveQueue(int bufferSize)
    : m_BufferSize(bufferSize)
{
    m_Buffer = new char[m_BufferSize];
    memset(m_Buffer, 0, static_cast<size_t>(m_BufferSize));
    m_Cursor = 0;
}

ReceiveQueue::~ReceiveQueue()
{
    delete m_Buffer;
}

int ReceiveQueue::receive(TransmissionSocket* socket)
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

bool ReceiveQueue::messageReadyForProcessing() const
{
    unsigned short messageSize = getFirstDataSize();

    return ((m_Cursor >= messageSize + 3) && (messageSize != 0));
}

void ReceiveQueue::getMessage(MessageContainer* messageContainer)
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

int ReceiveQueue::getAvailableBytes() const
{
    return m_BufferSize - m_Cursor;
}

unsigned short ReceiveQueue::getFirstDataSize() const
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

unsigned char ReceiveQueue::getFirstHeader() const
{
    if (m_Cursor < 3)
    {
        return 0;
    }
    else
    {
        return static_cast<unsigned char>(m_Buffer[2]);
    }
}
