project(proj_sock)


add_library(
        sock STATIC
        baseSocket.cpp
)

target_include_directories(
        sock
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE
        src
)
