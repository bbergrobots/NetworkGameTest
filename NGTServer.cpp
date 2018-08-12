//
// Created by Brendan Berg on 10.06.18.
//

#include <map/server/fileMap.hpp>
#include <player/server/playerCollection.hpp>

#include <chrono>
#include <iostream>
#include <thread>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Server Boot\n";
    std::cout << "===========================\n\n";

    FileMap map(2, "map.bin");
    PlayerCollection playerCollection(new PlayerListener(1337));
    playerCollection.registerMessageReceiver(&map);

    auto start = std::chrono::system_clock::now();
    auto end = start + std::chrono::seconds(60);

    while (std::chrono::system_clock::now() < end)
    {
        playerCollection.update();
    }

    std::cout << "Terminate server execution\n\n";

    return 0;
}
