//
// Created by Brendan Berg on 10.06.18.
//

#include <mapHandler.hpp>
#include <serverHandler.hpp>

#include <iostream>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Client Boot\n";
    std::cout << "===========================\n\n";

    ServerHandler serverHandler("127.0.0.1", 1337);

    MapHandler mapHandler;
    serverHandler.addServerRecvHandler(&mapHandler);

    serverHandler.activateConnection();

    while (serverHandler.isServerConnected());

    return 0;
}