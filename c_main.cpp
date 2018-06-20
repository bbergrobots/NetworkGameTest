//
// Created by Brendan Berg on 10.06.18.
//

#include <clibs/serverHandler.hpp>

#include <iostream>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Client Boot\n";
    std::cout << "===========================\n\n";

    ServerHandler serverHandler("127.0.0.1", 1337);

    while (serverHandler.isServerConnected());

    return 0;
}