cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetris)

enable_testing()

set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

if(${WITH_MOCK})
    set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DWITH_MOCK" )
endif(${WITH_MOCK}) 

set(TETRIS_CORE_LIBRARY tetris_core)
set(TETRIS_CORE_INCLUDE ${CMAKE_SOURCE_DIR}/core)

set(TETRIS_GTK_LIBRARY tetris_gtk)
set(TETRIS_GTK_INCLUDE ${CMAKE_SOURCE_DIR}/gtk)

add_subdirectory(core)
add_subdirectory(gtk)
