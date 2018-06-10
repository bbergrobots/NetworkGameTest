cmake_minimum_required(VERSION 3.9)
project(NetworkGameTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(NetworkGameTestServer s_main.cpp)
add_executable(NetworkGameTestClient c_main.cpp)