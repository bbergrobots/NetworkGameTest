//
// Created by Brendan Berg on 23.06.18.
//

#include "map/baseMap.hpp"

#include <cstring>
#include <random>
#include <iostream>


BaseMap::BaseMap(unsigned int size)
    : m_Size(size)
{
    m_ByteNo = 8 * m_Size * m_Size;
    m_MapData = new unsigned char[m_ByteNo];
    memset(m_MapData, '\0', m_ByteNo);
}

BaseMap::~BaseMap()
{
    delete m_MapData;
}

void BaseMap::initRandomly()
{
    std::default_random_engine engine;
    std::uniform_int_distribution<unsigned char> distribution(0, 255);

    for (int i = 0; i < m_ByteNo; i++)
    {
        m_MapData[i] = distribution(engine);
    }
}

void BaseMap::print()
{
    std::cout << "Printing current map:\n    ";

    for (int i = 0; i < m_ByteNo; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            std::cout << (m_MapData[i] >> j & 1);
        }

        if ((i + 1) % m_Size == 0)
        {
            std::cout << "\n    ";
        }
    }

    std::cout << '\n';
}

unsigned char* BaseMap::getMapData()
{
    return m_MapData;
}
