#include "grid.h"
#include <stdlib.h>

Grid* grid_new(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    Grid* grid = (Grid*) malloc(sizeof(Grid));
    grid->numberOfRows = numberOfRows;
    grid->numberOfColumns = numberOfColumns;
    grid->tetrominoTypes = (TetrominoType*) malloc(sizeof(TetrominoType) * 
                                                   numberOfRows * 
                                                   numberOfColumns);
    return grid;
}

void grid_destroy(Grid* grid)
{
    free(grid->tetrominoTypes);
    free(grid);
}
