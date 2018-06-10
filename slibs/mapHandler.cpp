//
// Created by Brendan Berg on 10.06.18.
//

#include "mapHandler.hpp"

#include <iostream>
#include <sys/stat.h>


MapHandler::MapHandler(const char *filename)
{
    bool flag = false;

    // check if file <filename> exist
    {
        struct stat buf{};
        if (stat(filename, &buf) == -1)
        {
            std::ofstream f;
            f.open(filename, std::ios::out);
            f.close();
            flag = true;
        }
    }

    m_File.open(filename, std::ios::in | std::ios::out | std::ios::binary);

    if (flag)
    {
        std::cout << "No map file detected. Going to generate new map.\n";
        initializeMap();
        saveEntireMap();
    }
    else
    {
        std::cout << "Map file detected. Going to load map from file.\n";
        loadMap();
    }

    m_File.seekg(0);
    m_File.seekp(0);

    m_Map = new char[16*2];
}

MapHandler::~MapHandler()
{
    m_File.close();
    delete m_Map;
}

void MapHandler::initializeMap()
{
    for(size_t i = 0; i < 16 * 2; i++)
    {
        m_Map[i] = (char) (rand() & 0xff);
    }
}

void MapHandler::saveEntireMap()
{
    if (m_File.is_open())
    {
        m_File.seekp(0);
        m_File.write(m_Map, 16 * 2);
    }
}

void MapHandler::loadMap()
{
    if (m_File.is_open())
    {
        m_File.seekg(0, std::ios::end);
        if (m_File.tellg() < 16 * 2 - 1)
        {
            std::cout << "Map file to small. Going to generate new map.\n";
            initializeMap();
            saveEntireMap();
        }
        else
        {
            m_File.seekg(0);
            m_File.read(m_Map, 16 * 2);
        }
    }
}
