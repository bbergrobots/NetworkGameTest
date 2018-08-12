//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_MESSAGECONTAINER_HPP
#define NETWORKGAMETEST_MESSAGECONTAINER_HPP

#include <string>


// TODO: add functions to copy buffer contents to provided buffer / from provided buffer
/**
 * @brief class that represents a socket message on the application layer containing decoded header information
 */
class MessageContainer
{

public:

    /**
     * @brief constructor allocates memory for message buffer and initializes all header information
     * @param bufferSize number of bytes for the message buffer
     */
    explicit MessageContainer(int bufferSize);

    /**
     * @brief destructor deallocates memory used by the message buffer
     */
    ~MessageContainer();

    /**
     * @brief set the actual data size of a message
     * @param dataSize number of bytes used by the message
     */
    void setDataSize(unsigned short dataSize);

    /**
     * @brief set the actual header of a message
     * @param header single byte header
     */
    void setHeader(unsigned char header);

    /**
     * @brief get the actual size of a message
     * @return number of bytes used by the message
     */
    unsigned short getDataSize() const;

    /**
     * @brief get the actual header of a message
     * @return single byte header
     */
    unsigned char getHeader() const;

    /**
     * @brief get the position of the data describing the message to copy it around
     * @return pointer to the first byte of the message
     */
    unsigned char* getBufferStart() const;

    /**
     * @brief print the contained message in the console
     */
    void print(std::string label) const;


private:

    /**
     * @brief number of bytes for the message buffer
     */
    int m_BufferSize;

    /**
     * @brief actual size of the message
     */
    unsigned short m_DataSize;

    /**
     * @brief actual header of the message
     */
    unsigned char m_Header;

    /**
     * @brief pointer to the first byte of the message
     */
    unsigned char* m_Data;


};


#endif //NETWORKGAMETEST_MESSAGECONTAINER_HPP
