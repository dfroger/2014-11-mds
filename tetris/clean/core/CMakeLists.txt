include_directories(${TETRIS_CORE_INCLUDE})

add_library(${TETRIS_CORE_LIBRARY} SHARED
    rgb_color.c
    piece.c
    tetromino.c
    tetromino_srs.c
    positionInGrid.c
)

add_subdirectory(test)
