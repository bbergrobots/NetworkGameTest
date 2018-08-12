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

    m_File.open(filename, std::ios::in | std::ios::out | std::ios::binary);

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

    m_File.seekg(0);
    m_File.seekp(0);
}

FileMap::~FileMap()
{
    m_File.close();
}

int FileMap::saveToFile()
{
    if (m_File.is_open())
    {
        m_File.seekp(0);
        m_File.write(reinterpret_cast<char*>(m_MapData), m_ByteNo);

        return 0;
    }

    return -1;
}

int FileMap::loadFromFile()
{
    if (m_File.is_open())
    {
        if (getFileSize() < m_ByteNo)
        {
            initRandomly();
            saveToFile();
        }
        else
        {
            m_File.seekg(0);
            m_File.read(reinterpret_cast<char*>(m_MapData), m_ByteNo);
        }

        return 0;
    }

    return -1;
}

int FileMap::getFileSize()
{
    if (m_File.is_open())
    {
        m_File.seekg(0, std::ios::end);

        return static_cast<int>(m_File.tellg());
    }

    return -1;
}

void FileMap::sendEntireMapToPlayer(Player* player) const
{
    MessageContainer msgContainer(m_ByteNo);
    msgContainer.setHeader(0x10);
    msgContainer.setDataSize(static_cast<unsigned short>(m_ByteNo));
    memcpy(msgContainer.getBufferStart(), m_MapData, m_ByteNo);

    player->getNetworkComponent()->sendMessage(&msgContainer);
}

bool FileMap::canProcessData(PlayerMessageContainer* messageContainer) const
{
    return ((messageContainer->getHeader() == 0x00) && (messageContainer->getDataSize() == 0));
}

void FileMap::processData(PlayerMessageContainer* messageContainer)
{
    if ((messageContainer->getHeader() == 0x00) && (messageContainer->getDataSize() == 0))
    {
        std::cout << "Send map to new connected player\n\n";
        sendEntireMapToPlayer(messageContainer->getPlayer());
    }
}
