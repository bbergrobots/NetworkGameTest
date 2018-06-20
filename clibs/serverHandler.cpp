//
// Created by Brendan Berg on 16.06.18.
//

#include "serverHandler.hpp"

#include <cassert>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>


ServerHandler::ServerHandler(const char *serverAddr, short serverPort)
{
    int ret, tmp, yes = 1;

    // create socket
    m_SockFD = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_SockFD != -1);

    // set socket options
    ret = setsockopt(m_SockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    assert(ret != -1);

    // assign address information to socket
    m_ClientAddr.sin_family = AF_INET;
    m_ClientAddr.sin_port = 0;
    m_ClientAddr.sin_addr.s_addr = 0; // auto address
    memset(&(m_ClientAddr.sin_zero), '\0', 8);

    struct in_addr hostInAddr{};
    inet_aton(serverAddr, &hostInAddr); // can fail --> returns 0
    m_HostAddr.sin_family = AF_INET;
    m_HostAddr.sin_port = htons(serverPort);
    m_HostAddr.sin_addr = hostInAddr;
    memset(&(m_HostAddr.sin_zero), '\0', 8);

    // bind socket to address
    ret = bind(m_SockFD, (struct sockaddr *) &m_ClientAddr, sizeof(struct sockaddr));
    assert(ret != -1);

    // connect to server
    ret = connect(m_SockFD, (struct sockaddr *) &m_HostAddr, sizeof(struct sockaddr));
    assert(ret != -1);

    // set non-blocking mode
    tmp = fcntl(m_SockFD, F_GETFL);
    tmp |= O_NONBLOCK;
    fcntl(m_SockFD, F_SETFL, tmp);

    m_ServerConnectedMutex.lock();
    m_ServerConnected = true;
    m_ServerConnectedMutex.unlock();

    m_RunningMutex.lock();
    m_Running = true;
    m_RunningMutex.unlock();
    m_UpdateThread = std::thread([this] {
        this->update();
    });
}

ServerHandler::~ServerHandler()
{
    m_RunningMutex.lock();
    m_Running = false;
    m_RunningMutex.unlock();
    m_UpdateThread.join();

    close(m_SockFD);
}

bool ServerHandler::isServerConnected() const
{
    return m_ServerConnected;
}

void ServerHandler::update()
{
    ssize_t len;
    char buf[1024];

    while(m_Running && m_ServerConnected)
    {
        len = recv(m_SockFD, &buf, 1024, 0);

        switch (len)
        {
        case -1:
            break;
        case 0:
            std::cout << "Server disconnected!\n";
            m_ServerConnectedMutex.lock();
            m_ServerConnected = false;
            m_ServerConnectedMutex.unlock();
            break;
        default:
            std::cout << "Receiving message from server:\n    ";
            for(ssize_t i = 0; i < len; i++)
            {
                std::cout << buf[i];
            }
            std::cout << '\n';
            const char *msg = "Hello, world!";
            send(m_SockFD, msg, 13, 0);
        }
    }
}
