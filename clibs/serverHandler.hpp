//
// Created by Brendan Berg on 16.06.18.
//

#ifndef NETWORKGAMETEST_SERVERHANDLER_HPP
#define NETWORKGAMETEST_SERVERHANDLER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>


class ServerHandler
{
public:

    ServerHandler(const char* serverAddr, short serverPort);

    ~ServerHandler();

    bool isServerConnected() const;

    void update();

private:

    int m_SockFD;

    struct sockaddr_in m_HostAddr;
    struct sockaddr_in m_ClientAddr;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;

    std::mutex m_ServerConnectedMutex;
    bool m_ServerConnected;
};


#endif //NETWORKGAMETEST_SERVERHANDLER_HPP
