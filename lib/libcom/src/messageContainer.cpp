//
// Created by Brendan Berg on 10.07.18.
//

#include "com/messageContainer.hpp"

#include <iostream>


MessageContainer::MessageContainer(int bufferSize)
    : m_BufferSize(bufferSize)
{
    m_Data = new unsigned char[m_BufferSize];
    memset(m_Data, 0, static_cast<size_t>(m_BufferSize));
    m_DataSize = 0;
    m_Header = 0x00;
}

MessageContainer::~MessageContainer()
{
    delete m_Data;
}

void MessageContainer::setDataSize(unsigned short dataSize)
{
    m_DataSize = dataSize;
}

void MessageContainer::setHeader(unsigned char header)
{
    m_Header = header;
}

unsigned short MessageContainer::getDataSize() const
{
    return m_DataSize;
}

unsigned char MessageContainer::getHeader() const
{
    return m_Header;
}

unsigned char* MessageContainer::getBufferStart()
{
    return m_Data;
}

void MessageContainer::print()
{
    std::cout << "Print message from server:\n";
    std::cout << "      Size: " <<  m_DataSize  << '\n';
    std::cout << "    Header: 0x" << std::hex << static_cast<int>(m_Header) << '\n';
    std::cout << "      Data: ";

    for (int i = 0; i < m_DataSize; i++)
    {
        if ((i % 8 == 0) && (i != 0))
        {
            std::cout << "            ";
        }
        std::cout << "0x" << static_cast<short>(m_Data[i]) << ' ';
        if (((i + 1) % 8 == 0) && ((i+1) != m_DataSize))
        {
            std::cout << '\n';
        }
    }

    std::cout << "\n\n";
    std::cout << std::dec;
}
