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

void grid_clear(Grid* grid);
void grid_set_cell(Grid* grid, PositionInGrid pos, TetrominoType type);
TetrominoType grid_get_cell(Grid* grid, PositionInGrid pos);

#endif
