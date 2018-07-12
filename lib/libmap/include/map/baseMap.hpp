//
// Created by Brendan Berg on 23.06.18.
//

#ifndef NETWORKGAMETEST_BASEMAP_HPP
#define NETWORKGAMETEST_BASEMAP_HPP


/**
 * @brief class that represents the game map
 */
class BaseMap
{

public:

    /**
     * @brief constructor allocates memory for map
     * @param size number of 8x8 chunks per dimension
     */
    explicit BaseMap(unsigned int size);

    /**
     * @brief destructor deallocates memory of map
     */
    virtual ~BaseMap();

    /**
     * @brief initialize map with random fields
     */
    void initRandomly();

    /**
     * @brief print map data in the console
     */
    void print() const;

    /**
     * @brief get raw map data
     * @return pointer to first map byte
     */
    unsigned char* getMapData() const;


protected:

    /**
     * @brief number of 8x8 chunks per dimension
     */
    unsigned int m_Size;

    /**
     * @brief number of bytes the map needs
     */
     unsigned int m_ByteNo;

    /**
     * @brief buffer for raw map data
     */
    unsigned char* m_MapData;


};


#endif //NETWORKGAMETEST_BASEMAP_HPP
