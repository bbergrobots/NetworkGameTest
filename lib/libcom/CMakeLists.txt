add_library(
        com STATIC
        src/serverConnectionHandler.cpp
        src/messageContainer.cpp
        src/receiveBufferQueue.cpp
)

target_include_directories(
        com
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/client>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(com sock)