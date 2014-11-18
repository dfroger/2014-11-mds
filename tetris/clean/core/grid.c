#include "grid.h"
#include <stdlib.h>

Grid* grid_new(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    /* Allocate grid */
    Grid* grid = (Grid*) malloc(sizeof(Grid));

    /* Set number of rows and columns */
    grid->numberOfRows = numberOfRows;
    grid->numberOfColumns = numberOfColumns;

    /* Allocate a classical C-style 2D array: creates an array of numberOfRows
     * pointers, each one pointing to contiguous memory of the column data. */
    grid->tetrominoTypes = (TetrominoType**)
        malloc(sizeof(TetrominoType*) * numberOfRows);
    unsigned int rowIndex;
    for (rowIndex = 0 ; rowIndex < numberOfRows ; rowIndex++)
    {
        grid->tetrominoTypes[rowIndex] = (TetrominoType*)
            malloc(sizeof(TetrominoType) * numberOfColumns);
    }

    return grid;
}

void grid_destroy(Grid* grid)
{
    /* Deallocate C-style 2D array */
    unsigned int rowIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows ; rowIndex++)
    {
        free(grid->tetrominoTypes[rowIndex]);
    }
    free(grid->tetrominoTypes);

    /* Deallocate grid */
    free(grid);
}
