//
// Created by Brendan Berg on 10.06.18.
//

#include <map/server/fileMap.hpp>
#include <playercon/server/playerConnectionController.hpp>

#include <iostream>
#include <thread>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Server Boot\n";
    std::cout << "===========================\n\n";

    FileMap map(2, "map.bin");

    PlayerConnectionController playerConnectionController(1337);

    auto t = std::chrono::seconds(20);
    std::this_thread::sleep_for(t);

    std::cout << "Terminate server execution\n\n";

    return 0;
}
