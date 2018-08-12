//
// Created by Brendan Berg on 23.06.18.
//

#ifndef NETWORKGAMETEST_FILEMAP_HPP
#define NETWORKGAMETEST_FILEMAP_HPP

#include "map/baseMap.hpp"

#include <net/messageReceiverInterface.hpp>
#include <net/messageContainer.hpp>
#include <player/server/playerMessageContainer.hpp>
#include <player/server/player.hpp>

#include <fstream>


/**
 * @brief class that represents the game map with it's associates save file
 */
class FileMap : public BaseMap, public MessageReceiverInterface<PlayerMessageContainer>
{

public:

    /**
     * @brief constructor opens and reads file
     * @param size number of 8x8 chunks per dimension
     * @param filename path to the associated file
     */
    FileMap(unsigned int size, const char* filename);

    /**
     * @brief destructor closes the file
     */
    ~FileMap() override;

    /**
     * @brief save entire map inside the associated file
     * @return 0 success
     * @return -1 failure
     */
    int saveToFile();

    /**
     * @brief load map from the associated file to memory
     * @return success or failure
     * @retval 0 success
     * @retval -1 failure
     */
    int loadFromFile();

    /**
     * @brief get size of map the associated file
     * @return file size in bytes
     */
    int getFileSize();

    /**
     * @brief send entire map data to specified player
     * @param player destination node
     */
    void sendEntireMapToPlayer(Player* player) const;

    /**
     * @brief implemented function checks whether the class can process the provided network message
     * @param messageContainer pointer to a received network message
     * @return class can or cannot process the provided network message
     */
    bool canProcessData(PlayerMessageContainer* messageContainer) const override;

    /**
     * @brief process the received network message
     * @param messageContainer pointer to a received network message
     */
    void processData(PlayerMessageContainer* messageContainer) override;



private:

    /**
     * @brief associated file
     */
    std::fstream m_File;

};


#endif //NETWORKGAMETEST_FILEMAP_HPP
