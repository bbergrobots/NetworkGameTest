//
// Created by Brendan Berg on 23.06.18.
//

#include "map/baseMap.hpp"

#include <cstring>
#include <random>
#include <iostream>


BaseMap::BaseMap(unsigned int size)
    : mSize(size)
{
    mByteNo = 8 * mSize * mSize;
    mMapData = new unsigned char[mByteNo];
    memset(mMapData, '\0', mByteNo);
}

BaseMap::~BaseMap()
{
    delete mMapData;
}

void BaseMap::initRandomly()
{
    std::default_random_engine engine;
    std::uniform_int_distribution<unsigned char> distribution(0, 255);

    for (int i = 0; i < mByteNo; i++)
    {
        mMapData[i] = distribution(engine);
    }
}

void BaseMap::print()
{
    std::cout << "Printing current map:\n    ";

    for (int i = 0; i < mByteNo; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            std::cout << (mMapData[i] >> j & 1);
        }

        if ((i + 1) % mSize == 0)
        {
            std::cout << "\n    ";
        }
    }

    std::cout << '\n';
}

unsigned char* BaseMap::getMapData()
{
    return mMapData;
}
