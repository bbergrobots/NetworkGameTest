//
// Created by Brendan Berg on 16.06.18.
//

#ifndef NETWORKGAMETEST_SERVERHANDLER_HPP
#define NETWORKGAMETEST_SERVERHANDLER_HPP

#include "serverRecvHandler.hpp"

#include <sock/baseSocket.hpp>
#include <sock/clientSocket.hpp>

#include <thread>
#include <mutex>
#include <list>


class ServerHandler
{
public:

    ServerHandler(const char* serverAddr, short serverPort);

    ~ServerHandler();

    void addServerRecvHandler(ServerRecvHandler* srh);

    void activateConnection();

    bool isServerConnected() const;

    void update();

private:

//    BaseSocket m_Socket;
    ClientSocket m_Socket;

    std::thread m_UpdateThread;

    std::mutex m_RunningMutex;
    bool m_Running;

    std::mutex m_ServerConnectedMutex;
    bool m_ServerConnected;

    std::list<ServerRecvHandler*> m_ServerRecvHandler;

    void printRecvData(unsigned char* rawData, int length) const;
};


#endif //NETWORKGAMETEST_SERVERHANDLER_HPP
