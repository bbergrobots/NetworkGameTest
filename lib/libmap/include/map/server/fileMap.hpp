//
// Created by Brendan Berg on 23.06.18.
//

#ifndef NETWORKGAMETEST_FILEMAP_HPP
#define NETWORKGAMETEST_FILEMAP_HPP

#include "map/baseMap.hpp"

#include <fstream>


/**
 * @brief class that represents the game map with it's associates save file
 */
class FileMap : public BaseMap
{
public:

    /**
     * @brief constructor opens and reads file
     * @param size number of 8x8 chunks per dimension
     * @param filename path to associated file
     */
    explicit FileMap(unsigned int size, const char* filename);

    /**
     * @brief destructor closes file
     */
    ~FileMap() override;

    /**
     * @brief save entire map in associated file
     * @return 0 success
     * @return -1 failure
     */
    int saveToFile();

    /**
     * @brief load map from file to memory
     * @return 0 success
     * @return -1 failure
     */
    int loadFromFile();

    /**
     * @brief get size of map file
     * @return file size in bytes
     */
    int getFileSize();


private:

    /**
     * @brief associated file
     */
    std::fstream mFile;

};


#endif //NETWORKGAMETEST_FILEMAP_HPP
