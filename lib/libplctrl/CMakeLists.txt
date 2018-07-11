add_library(
        plctrl STATIC
        src/playerConnection.cpp
        src/playerConnectionController.cpp
        src/playerController.cpp
)

target_include_directories(
        plctrl
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/server>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(plctrl com sock)