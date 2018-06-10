cmake_minimum_required(VERSION 3.9)
project(NetworkGameTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(slibs)

add_executable(NetworkGameTestServer s_main.cpp)
add_executable(NetworkGameTestClient c_main.cpp)

target_link_libraries(NetworkGameTestServer slibs)
