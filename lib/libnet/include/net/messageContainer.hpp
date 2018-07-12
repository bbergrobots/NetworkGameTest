//
// Created by Brendan Berg on 10.07.18.
//

#ifndef NETWORKGAMETEST_MESSAGECONTAINER_HPP
#define NETWORKGAMETEST_MESSAGECONTAINER_HPP


class MessageContainer
{

public:

    explicit MessageContainer(int bufferSize);

    ~MessageContainer();

    void setDataSize(unsigned short dataSize);

    void setHeader(unsigned char header);

    unsigned short getDataSize() const;

    unsigned char getHeader() const;

    unsigned char* getBufferStart();

    void print();


private:

    int m_BufferSize;

    unsigned short m_DataSize;

    unsigned char m_Header;

    unsigned char* m_Data;


};


#endif //NETWORKGAMETEST_MESSAGECONTAINER_HPP
