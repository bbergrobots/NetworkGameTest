add_library(
        sock STATIC
        src/baseSocket.cpp
        src/listeningSocket.cpp
        src/sessionSocket.cpp
)

target_include_directories(
        sock
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)
