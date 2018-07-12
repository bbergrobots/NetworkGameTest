add_library(
        player STATIC
        src/player.cpp
        src/playerCollection.cpp
        src/playerListener.cpp
        src/playerNetworkComponent.cpp
)

target_include_directories(
        player
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/server>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(player net sock)
