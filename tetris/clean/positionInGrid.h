#ifndef TETRIS_POSITION_IN_GRID_H
#define TETRIS_POSITION_IN_GRID_H

#include <stdbool.h>

struct positionInGrid
{
  int rowIndex;
  int columnIndex;
};
typedef struct positionInGrid PositionInGrid;

bool samePositionsInGrid(PositionInGrid const left, PositionInGrid const right);

#endif

