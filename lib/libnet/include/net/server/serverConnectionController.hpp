//
// Created by Brendan Berg on 11.07.18.
//

#ifndef NETWORKGAMETEST_SERVERCONNECTIONCONTROLLER_HPP
#define NETWORKGAMETEST_SERVERCONNECTIONCONTROLLER_HPP

#include <sock/listeningSocket.hpp>
#include <sock/sessionSocket.hpp>

#include <list>
#include <mutex>
#include <thread>


/**
 * @brief class that manages all incoming socket connections of the server
 */
class ServerConnectionController
{

public:

    /**
     * @brief constructor sets up the listening socket and starts the update thread
     * @param hostPort the port number the controller is assigned to, use 0 for any open port
     */
    explicit ServerConnectionController(unsigned short hostPort);

    /**
     * @brief destructor joins the update thread and destructs all unassigned session sockets
     */
    ~ServerConnectionController();

    /**
     * @brief checks whether new clients have established a connection to this server
     * @return are new clients available
     */
    bool newClientAvailable();

    /**
     * @brief get the connection to a new client and remove it from the internal queue
     * @return pointer to the socket connected with the first incoming client
     * @retval nullptr no new client available
     */
    SessionSocket* getNewClient();


private:

    /**
     * @brief socket to use for the listening
     */
    ListeningSocket m_Socket;

    // TODO: use main thread because listening in non-blocking mode isn't time intensive
    /**
     * @brief thread that waits for incoming socket connections and adds them to the queue
     */
    std::thread m_UpdateThread;

    /**
     * @brief flag to notify the update thread to end up its activities
     */
    bool m_Running;

    /**
     * @brief mutex to make the incoming sockets queue thread safe
     */
    std::mutex m_NewSessionSocketsMtx;

    /**
     * @brief list of all unassigned session sockets
     */
    std::list<SessionSocket*> m_NewSessionSockets;

    /**
     * @brief function that runs inside the update thread
     */
    void update();
};


#endif //NETWORKGAMETEST_SERVERCONNECTIONCONTROLLER_HPP
