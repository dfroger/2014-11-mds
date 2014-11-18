#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H

#include "tetromino.h"

typedef struct grid {
    TetrominoType** tetrominoTypes;
    unsigned int numberOfRows;
    unsigned int numberOfColumns;
} Grid;

Grid* grid_new(unsigned int numberOfRows, unsigned int numberOfColumns);
void grid_destroy(Grid* grid);

#endif
