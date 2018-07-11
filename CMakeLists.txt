cmake_minimum_required(VERSION 3.9)
project(NetworkGameTest)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(NetworkGameTestServer NGTServer.cpp)
add_executable(NetworkGameTestClient NGTClient.cpp)

target_link_libraries(NetworkGameTestServer PUBLIC slibs sock map playercon)
target_link_libraries(NetworkGameTestClient PUBLIC sock map com)

add_custom_target(All)
add_dependencies(All NetworkGameTestServer NetworkGameTestClient)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(Documentation ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            VERBATIM)
endif(DOXYGEN_FOUND)