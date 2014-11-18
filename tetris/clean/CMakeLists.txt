cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetris)

SET( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

set(SOURCES
    #${CMAKE_SOURCE_DIR}/window.c 
    #${CMAKE_SOURCE_DIR}/grid.c 
    #${CMAKE_SOURCE_DIR}/point.c 
    ${CMAKE_SOURCE_DIR}/core/piece.c
    ${CMAKE_SOURCE_DIR}/core/tetromino.c
    ${CMAKE_SOURCE_DIR}/core/rgb_color.c
    ${CMAKE_SOURCE_DIR}/core/positionInGrid.c
)

add_executable(tetris gtk/tetris.c ${SOURCES})

find_package(GTK2 2.6 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})
target_link_libraries(tetris ${GTK2_LIBRARIES})

add_subdirectory(core/test)

