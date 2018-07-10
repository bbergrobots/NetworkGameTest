//
// Created by Brendan Berg on 10.06.18.
//

#ifndef NETWORKGAMETEST_PLAYER_HPP
#define NETWORKGAMETEST_PLAYER_HPP

#include <sock/sessionSocket.hpp>

//network
#include <netinet/in.h>
//thread
#include <thread>
#include <mutex>


class Player
{
public:

    explicit Player(SessionSocket* socket);

    ~Player();

    void update();

    bool isClientConnected() const;

    void sendRawData(unsigned char* data, int length) const;

    void sendMap(unsigned char* mapData) const;


private:

    SessionSocket* m_Socket;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;

    std::mutex m_ClientConnectedMutex;
    bool m_ClientConnected;
};


#endif //NETWORKGAMETEST_PLAYER_HPP
