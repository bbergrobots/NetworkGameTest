//
// Created by Brendan Berg on 10.06.18.
//

#include <net/client/clientConnectionController.hpp>
#include <map/client/networkMap.hpp>

#include <iostream>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Client Boot\n";
    std::cout << "===========================\n\n";

    ClientConnectionController clientConnectionController("127.0.0.1", 1337);

    NetworkMap map(2);
    clientConnectionController.registerMessageReceiver(&map);

    clientConnectionController.establishConnection();

    while (clientConnectionController.isServerConnected());

    return 0;
}