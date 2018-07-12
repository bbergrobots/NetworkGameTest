add_library(
        net STATIC
        src/clientConnectionController.cpp
        src/messageContainer.cpp
        src/receiveQueue.cpp
        src/serverConnectionController.cpp
        src/sendQueue.cpp
)

target_include_directories(
        net
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/client>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/server>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(net sock)