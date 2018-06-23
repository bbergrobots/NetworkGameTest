//
// Created by Brendan Berg on 16.06.18.
//

#include "mapHandler.hpp"

#include <iostream>


MapHandler::MapHandler()
{
    m_Map = new unsigned char[16 * 2];
    memset(m_Map, 0, 16 * 2);

    print();
}

MapHandler::~MapHandler()
{
    delete m_Map;
}

bool MapHandler::canHandleData(unsigned short dataCode, size_t length) const
{
    if (dataCode >> 8 == 0x10)
    {
        if (length == 16 * 2)
        {
            return true;
        }
    }

    return false;
}

void MapHandler::recvData(unsigned char *rawData, size_t length)
{
    if (rawData[0] == 0x10 && length == 16 * 2)
    {
        recvMap(rawData);
    }
}

void MapHandler::recvMap(unsigned char *rawData)
{
    memcpy(m_Map, rawData + 2, 16 * 2);
    print();
}

void MapHandler::print() const
{
    std::cout << "Printing current map:\n";
    for(unsigned int i = 0; i < 16 * 2; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << "    ";
        }

        for(unsigned int j = 0; j < 8; j++)
        {
            std::cout << (m_Map[i] >> j & 1u);
        }

        if (i % 2 == 1)
        {
            std::cout << '\n';
        }
    }
}
