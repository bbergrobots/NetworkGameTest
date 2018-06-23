cmake_minimum_required(VERSION 3.9)
project(NetworkGameTest)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(NetworkGameTestServer OMCServer.cpp)
add_executable(NetworkGameTestClient OMCClient.cpp)

target_link_libraries(NetworkGameTestServer PUBLIC slibs sock map)
target_link_libraries(NetworkGameTestClient PUBLIC clibs sock map)
