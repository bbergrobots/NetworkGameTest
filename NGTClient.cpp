//
// Created by Brendan Berg on 10.06.18.
//

#include <net/client/serverConnectionHandler.hpp>
#include <map/client/networkMap.hpp>

#include <iostream>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Client Boot\n";
    std::cout << "===========================\n\n";

    ServerConnectionHandler serverConnectionHandler("127.0.0.1", 1337);

    NetworkMap map(2);
    serverConnectionHandler.registerServerMessageReceiver(&map);

    serverConnectionHandler.establishConnection();

    while (serverConnectionHandler.isServerConnected());

    return 0;
}