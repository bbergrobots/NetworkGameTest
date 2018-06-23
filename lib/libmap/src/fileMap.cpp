//
// Created by Brendan Berg on 23.06.18.
//

#include "map/server/fileMap.hpp"

#include <sys/stat.h>
#include <iostream>


FileMap::FileMap(unsigned int size, const char *filename)
    : BaseMap(size)
{
    bool isFileNew = false;

    struct stat buf{};
    if (stat(filename, &buf) == -1)
    {
        std::ofstream f;
        f.open(filename, std::ios::out);
        f.close();
        isFileNew = true;
    }

    mFile.open(filename, std::ios::in | std::ios::out | std::ios::binary);

    if (isFileNew)
    {
        initRandomly();
        saveToFile();
    }
    else
    {
        loadFromFile();
    }

    print();

    mFile.seekg(0);
    mFile.seekp(0);
}

FileMap::~FileMap()
{
    mFile.close();
}

int FileMap::saveToFile()
{
    if (mFile.is_open())
    {
        mFile.seekp(0);
        mFile.write(reinterpret_cast<char*>(mMapData), mByteNo);

        return 0;
    }

    return -1;
}

int FileMap::loadFromFile()
{
    if (mFile.is_open())
    {
        if (getFileSize() < mByteNo)
        {
            initRandomly();
            saveToFile();
        }
        else
        {
            mFile.seekg(0);
            mFile.read(reinterpret_cast<char*>(mMapData), mByteNo);
        }

        return 0;
    }

    return -1;
}

int FileMap::getFileSize()
{
    if (mFile.is_open())
    {
        mFile.seekg(0, std::ios::end);

        return static_cast<int>(mFile.tellg());
    }

    return -1;
}
