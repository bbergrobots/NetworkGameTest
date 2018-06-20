//
// Created by Brendan Berg on 10.06.18.
//

#ifndef NETWORKGAMETEST_PLAYER_HPP
#define NETWORKGAMETEST_PLAYER_HPP

//network
#include <netinet/in.h>
//thread
#include <thread>
#include <mutex>


class Player
{
public:

    Player(int sockFD, struct sockaddr_in clientAddr);

    ~Player();

    void sendMap(char* mapData) const;

    void update();

    bool isClientConnected() const;


private:

    int m_SockFD;
    struct sockaddr_in m_ClientAddr;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;

    std::mutex m_ClientConnectedMutex;
    bool m_ClientConnected;
};


#endif //NETWORKGAMETEST_PLAYER_HPP
