//
// Created by Brendan Berg on 10.06.18.
//

#ifndef NETWORKGAMETEST_MAPHANDLER_HPP
#define NETWORKGAMETEST_MAPHANDLER_HPP

#include <fstream>


/**
 * @brief class that represents a game map associated with the save file
 */
class MapHandler
{
public:

    /**
     * @brief constructor opens (creates) the file and loads (generates) the map
     * @param filename name of the file containing the map save
     */
    explicit MapHandler(const char* filename);

    /**
     * @brief destructor closes the file and frees used memory
     */
    ~MapHandler();

    unsigned char* getMap() const;

private:

    /**
     * @brief file containing the map save
     */
    std::fstream m_File;

    /**
     * @brief buffer to work with containing the map
     */
    unsigned char* m_Map;

    /**
     * @brief generate a random map
     */
    void initializeMap();

    /**
     * @brief save map into file
     */
    void saveEntireMap();

    /**
     * @brief load map from file, regen in case of failure
     */
    void loadMap();
};


#endif //NETWORKGAMETEST_MAPHANDLER_HPP
