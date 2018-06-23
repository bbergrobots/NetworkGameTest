//
// Created by Brendan Berg on 10.06.18.
//

#include <mapHandler.hpp>
#include <playerHandler.hpp>

#include <iostream>
#include <thread>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Server Boot\n";
    std::cout << "===========================\n\n";

    MapHandler mapHandler("map.bin");
    PlayerHandler playerHandler(&mapHandler);

    auto t = std::chrono::seconds(180);
    std::this_thread::sleep_for(t);

    std::cout << "Terminating server execution\n";

    return 0;
}
