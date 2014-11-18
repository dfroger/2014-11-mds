include_directories(${TETRIS_CORE_INCLUDE})

add_library(${TETRIS_CORE_LIBRARY} SHARED
    piece.c
    tetromino.c
    positionInGrid.c
)

add_subdirectory(test)
