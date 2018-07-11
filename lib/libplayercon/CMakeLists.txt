add_library(
        playercon STATIC
        src/playerConnection.cpp
        src/playerConnectionController.cpp
)

target_include_directories(
        playercon
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/server>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(playercon com sock)