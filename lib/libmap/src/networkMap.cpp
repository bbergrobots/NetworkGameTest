//
// Created by Brendan Berg on 10.07.18.
//

#include "map/client/networkMap.hpp"

#include <cstring>


NetworkMap::NetworkMap(unsigned int size)
        : BaseMap(size)
{
    print();
}

bool NetworkMap::canProcessData(unsigned short header, int length) const
{
    if (header >> 8u == 0x10)
    {
        if (length == m_ByteNo)
        {
            return true;
        }
    }

    return false;
}

void NetworkMap::processData(void* rawData, int length)
{
    if (length == m_ByteNo)
    {
        memcpy(m_MapData, static_cast<char*>(rawData) + 2, static_cast<size_t>(m_ByteNo));
        print();
    }
}
