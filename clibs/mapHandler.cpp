//
// Created by Brendan Berg on 16.06.18.
//

#include "mapHandler.hpp"

#include <iostream>


MapHandler::MapHandler()
{
    m_Map = new char[16 * 2];
}

MapHandler::~MapHandler()
{

}

void MapHandler::print() const
{
    for(int i = 0; i < 16 * 2; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            std::cout << ((m_Map[i] >> j) & 0x01);
        }
        std::cout << '\n';
    }
}

void MapHandler::setMap(char* mapData)
{
    m_Map = mapData;
}
