//
// Created by Brendan Berg on 10.06.18.
//

#include <slibs/mapHandler.hpp>
#include <slibs/playerHandler.hpp>

#include <iostream>


int main()
{
    std::cout << "\n";
    std::cout << "NetworkGameTest Server Boot\n";
    std::cout << "===========================\n\n";

    MapHandler mapHandler("map.bin");
    PlayerHandler playerHandler(&mapHandler);

    auto t = std::chrono::seconds(20);
    std::this_thread::sleep_for(t);

    std::cout << "Finishing program execution\n";

    return 0;
}
