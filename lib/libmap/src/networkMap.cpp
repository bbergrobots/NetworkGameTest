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

bool NetworkMap::canProcessData(MessageContainer* msg) const
{
    return ((msg->getHeader() == 0x10) && (msg->getDataSize() == m_ByteNo));
}

void NetworkMap::processData(MessageContainer* msg)
{
    if (canProcessData(msg))
    {
        memcpy(m_MapData, msg->getBufferStart(), static_cast<size_t>(m_ByteNo));
        print();
    }
}
