add_library(
        map STATIC
        src/baseMap.cpp
        src/fileMap.cpp
)

target_include_directories(
        map
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)
