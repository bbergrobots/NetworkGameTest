//
// Created by Brendan Berg on 10.07.18.
//

#include "map/client/networkMap.hpp"

#include <cstring>


NetworkMap::NetworkMap(unsigned int size)
    : BaseMap(size)
{

}

bool NetworkMap::canProcessData(MessageContainer* messageContainer) const
{
    return ((messageContainer->getHeader() == 0x10) && (messageContainer->getDataSize() == m_ByteNo));
}

void NetworkMap::processData(MessageContainer* messageContainer)
{
    if (canProcessData(messageContainer))
    {
        memcpy(m_MapData, messageContainer->getBufferStart(), static_cast<size_t>(m_ByteNo));
        print();
    }
}
