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

    /* clear grid, ie intialize it to TETROMINO_VOID */
    grid_clear(grid);

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

void grid_clear(Grid* grid)
{
    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            grid->tetrominoTypes[rowIndex][columnIndex] = TETROMINO_VOID;
        }
    }
}

void grid_set_cell(Grid* grid, PositionInGrid pos, TetrominoType type)
{
    grid->tetrominoTypes[pos.rowIndex][pos.columnIndex] = type;
}

TetrominoType grid_get_cell(Grid* grid, PositionInGrid pos)
{
    return grid->tetrominoTypes[pos.rowIndex][pos.columnIndex];
}

void gridSetCellsWithPiece(Grid* grid, Piece* piece, TetrominoType type)
{
    unsigned squareIndex;
    PositionInGrid pos;

    for (squareIndex = 0 ; 
         squareIndex < TETROMINO_NUMBER_OF_SQUARES ;
         squareIndex++)
    {
        pos = piecePositionInGrid(piece, squareIndex);
        grid_set_cell(grid, pos, type);
    }
}

bool gridCellIsInGrid(Grid* grid, PositionInGrid pos)
{
    return 0 <= pos.rowIndex && pos.rowIndex < grid->numberOfRows &&
           0 <= pos.columnIndex && pos.columnIndex < grid->numberOfColumns;
}

bool gridCellIsInGridAndIsVoid(Grid* grid, PositionInGrid pos)
{
    return gridCellIsInGrid(grid,pos) && grid_get_cell(grid, pos) == TETROMINO_VOID;
}

bool gridCanSetCellsWithPiece(Grid* grid, Piece* piece)
{
    unsigned squareIndex;
    PositionInGrid pos;

    for (squareIndex = 0 ; 
         squareIndex < TETROMINO_NUMBER_OF_SQUARES ;
         squareIndex++)
    {
        pos = piecePositionInGrid(piece, squareIndex);
        if (! gridCellIsInGridAndIsVoid(grid,pos) ) return false;
    }

    return true;
}

bool sameGrids(Grid const * const left, Grid const * const right)
{
    // Compare grid dimensions.
    if (left->numberOfRows != right->numberOfRows)
        return false;
    if (left->numberOfColumns != right->numberOfColumns)
        return false;

    // Compare grid values.
    PositionInGrid pos;
    unsigned int rowIndex;
    unsigned int columnIndex;

    for (rowIndex = 0 ; rowIndex < left->numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < left->numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            if (grid_get_cell(left, pos) != grid_get_cell(right,pos)) {
               printf("sameGrid: (%u,%u): %u VS %u\n",pos.rowIndex, pos.columnIndex, grid_get_cell(left, pos), grid_get_cell(right,pos));
               return false; 
            }
        }
    }
    return true;
}
