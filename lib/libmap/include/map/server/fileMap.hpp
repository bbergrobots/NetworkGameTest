//
// Created by Brendan Berg on 23.06.18.
//

#ifndef NETWORKGAMETEST_FILEMAP_HPP
#define NETWORKGAMETEST_FILEMAP_HPP

#include "map/baseMap.hpp"

#include <fstream>


class FileMap : public BaseMap
{
public:

    explicit FileMap(unsigned int size, const char* filename);

    ~FileMap() override;

    int saveToFile();

    int loadFromFile();

    int getFileSize();


private:

    std::fstream mFile;

};


#endif //NETWORKGAMETEST_FILEMAP_HPP
