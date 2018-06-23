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
     * @brief print map data to console
     */
    void print();

    /**
     * @brief return raw map data
     * @return pointer to first map byte
     */
    unsigned char* getMapData();


protected:

    /**
     * @brief number of 8x8 chunks per dimension
     */
    unsigned int mSize;

    /**
     * @brief number of bytes needed by the map
     */
     unsigned int mByteNo;

    /**
     * @brief bytes of raw map data
     */
    unsigned char* mMapData;

};


#endif //NETWORKGAMETEST_BASEMAP_HPP
