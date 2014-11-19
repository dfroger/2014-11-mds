#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

#include "piece.h"
#include "tetromino_srs.h"
#include "grid.h"
#include "game.h"

static size_t random_row_index;
static size_t const ZERO = 0;

TetrominosCollection* tetrominosCollection;

/* Suite initialization */
int init_suite()
{
   /*random_row_index = rand() % NUMBER_OF_ROWS;*/
   tetrominosCollection = getTetrominosCollectionSRS();
   return 0;
}

/* Suite termination */
int clean_suite()
{
   tetrominosCollectionDestroy(tetrominosCollection);
   return 0;
}

#define ADD_TEST_TO_SUITE(suite,test) \
if ( ( CU_add_test(suite, #test, test) == NULL ) ) { \
    CU_cleanup_registry(); \
    return CU_get_error(); \
}

#define ADD_SUITE_TO_REGISTRY(suite) \
suite = CU_add_suite(#suite, init_suite, clean_suite); \
if ( suite == NULL ) { \
  CU_cleanup_registry(); \
  return CU_get_error(); \
}

//////////////////////////////////////////////////////////////////////////////
// Grid suite tests
//////////////////////////////////////////////////////////////////////////////

void test_grid_new_destroy()
{
    // Create a grid.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    // Check that values are initialized to TETROMINO_VOID
    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            CU_ASSERT(grid->tetrominoTypes[rowIndex][columnIndex] == TETROMINO_VOID);
        }
    }

    // Free memory.
    grid_destroy(grid);
}

void test_grid_set_get_cell()
{
    // Create a 3 rows grid.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    unsigned int columnIndex;
    PositionInGrid pos;

    // Set first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        grid_set_cell(grid, pos, TETROMINO_SRS_O);
    }

    // Set Third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        grid_set_cell(grid, pos, TETROMINO_SRS_I);
    }

    // Check first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( grid_get_cell(grid, pos) == TETROMINO_SRS_O);
    }

    // Check second row, it has been initialize to TETROMINO_VOID by grid_new.
    pos.rowIndex = 1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( grid_get_cell(grid, pos) == TETROMINO_VOID);
    }

    // Check third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( grid_get_cell(grid, pos) == TETROMINO_SRS_I);
    }
}

void testPiecePositionInGrid()
{
    // Create a piece;
    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];
    Piece piece = {{2,3},TETROMINO_I,ANGLE_90};

    // Expected result
    PositionInGrid expectedPos0 = {2,5};
    PositionInGrid expectedPos1 = {3,5};
    PositionInGrid expectedPos2 = {4,5};
    PositionInGrid expectedPos3 = {5,5};

    // Actual results
    PositionInGrid pos0 = piecePositionInGrid(&piece,0);
    PositionInGrid pos1 = piecePositionInGrid(&piece,1);
    PositionInGrid pos2 = piecePositionInGrid(&piece,2);
    PositionInGrid pos3 = piecePositionInGrid(&piece,3);

    // Check actual results versus expected.
    CU_ASSERT( samePositionsInGrid(pos0, expectedPos0) );
    CU_ASSERT( samePositionsInGrid(pos1, expectedPos1) );
    CU_ASSERT( samePositionsInGrid(pos2, expectedPos2) );
    CU_ASSERT( samePositionsInGrid(pos3, expectedPos3) );
}

void testGridSetCellsWithPiece()
{
    // Create a grid.
    unsigned int numberOfRows = 10;
    unsigned int numberOfColumns = 10;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    // Create a piece;
    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];
    Piece piece = {{2,3},TETROMINO_I,ANGLE_90};

    gridSetCellsWithPiece(grid, &piece, piece.tetromino.type);

    // The piece position in grid.
    PositionInGrid pos0 = {2,5};
    PositionInGrid pos1 = {3,5};
    PositionInGrid pos2 = {4,5};
    PositionInGrid pos3 = {5,5};
    PositionInGrid pos;

    TetrominoType type;
    TetrominoType expectedType;

    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            pos.rowIndex = rowIndex;
            pos.columnIndex = columnIndex;
            if (samePositionsInGrid(pos, pos0) ||
                samePositionsInGrid(pos, pos1) ||
                samePositionsInGrid(pos, pos2) ||
                samePositionsInGrid(pos, pos3))
            {
                expectedType = TETROMINO_SRS_I;
            } else {
                expectedType = TETROMINO_VOID;
            }
            type = grid_get_cell(grid,pos);
            CU_ASSERT_EQUAL(type,expectedType);
        }
    }
}

void TestGridCellIsInGrid()
{
    // Create a grid.
    unsigned int numberOfRows = 2;
    unsigned int numberOfColumns = 3;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    PositionInGrid pos;
    unsigned int rowIndex;
    unsigned int columnIndex;

    // Check position that are in grid
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            CU_ASSERT_TRUE(gridCellIsInGrid(grid, pos));
        }
    }

    // Check row out of grid from top.
    pos.rowIndex = -1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(gridCellIsInGrid(grid, pos));
    }

    // Check row out of grid from bottom.
    pos.rowIndex = numberOfRows;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(gridCellIsInGrid(grid, pos));
    }

    // Check column out of grid from left.
    pos.columnIndex = -1;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(gridCellIsInGrid(grid, pos));
    }

    // Check column out of grid from right.
    pos.columnIndex = numberOfColumns;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(gridCellIsInGrid(grid, pos));
    }
}

void TestGridCellIsInGridAndIsVoid()
{
    // Create a grid.
    unsigned int numberOfRows = 2;
    unsigned int numberOfColumns = 3;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    // Grid has been initialize to TETROMINO_VOID, modify one cell type.
    PositionInGrid posNotVoid = {1,2};
    grid_set_cell(grid, posNotVoid, TETROMINO_SRS_O);

    unsigned int rowIndex;
    unsigned int columnIndex;
    PositionInGrid pos;
    bool isInGridAndIsVoid;

    // Check for cells in grid.
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            isInGridAndIsVoid = gridCellIsInGridAndIsVoid(grid,pos);
            if (samePositionsInGrid(pos,posNotVoid)) {
                CU_ASSERT_FALSE(isInGridAndIsVoid);
            } else {
                CU_ASSERT_TRUE(isInGridAndIsVoid);
            }
        }
    }

    // Check for cell NOT in grid.
    pos.rowIndex = 5;
    pos.columnIndex = 5;
    isInGridAndIsVoid = gridCellIsInGridAndIsVoid(grid,pos);
    CU_ASSERT_FALSE(isInGridAndIsVoid);
}

void TestGridCanSetCellsWithPiece()
{

    /* Reminder on tetromino_srs_i at ANGLE_0 and ANGLE_90:

    T---+---+---+---+
    |   |   |  9|   |   T: topLeftCorner position in grid
    +---+---+---+---+   0: tetromino cells a ANGLE_0
    | 0 | 0 | 01| 0 |   9: tetromino cells a ANGLE_90
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    */

    // Create a grid.
    unsigned int numberOfRows = 10;
    unsigned int numberOfColumns = 10;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

    // For now, the grid has only void cells.

    // Ok, in grid and void.
    Piece piece0 = {{0,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece0) )

    // Ok, still in grid (in the first row).
    Piece piece1 = {{-1,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece1) )

    // No more in grid.
    Piece piece2 = {{-2,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_FALSE( gridCanSetCellsWithPiece(grid, &piece2) )

    // Ok, in grid and void.
    Piece piece3 = {{5,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece3) )

    // Ok, still in grid (in the first column).
    Piece piece4 = {{5,-2},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece4) )

    // No more in grid.
    Piece piece5 = {{5,-3},TETROMINO_I,ANGLE_90};
    CU_ASSERT_FALSE( gridCanSetCellsWithPiece(grid, &piece5) )

    // Now, fill the last grid row with non-void tetrominos.
    PositionInGrid pos;
    unsigned int columnIndex;
    pos.rowIndex = numberOfRows-1 ;
    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        grid_set_cell(grid, pos, TETROMINO_SRS_I);
    }

    // Ok, in grid and void.
    Piece piece6 = {{0,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece6) )

    // Still in grid and void, just above the non-void row.
    Piece piece7 = {{numberOfRows-5,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( gridCanSetCellsWithPiece(grid, &piece7) )

    // In grid, but last cell of piece overlap a non-void cell of the grid.
    Piece piece8 = {{numberOfRows-4,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_FALSE( gridCanSetCellsWithPiece(grid, &piece8) )
}

/*
void test_set_row_to_zero()
{
  size_t columnIndex;
  set_row_to_zero(random_row_index);
  for ( columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex )
    CU_ASSERT( game.grid[random_row_index][columnIndex] == ZERO )
  
}

void test_set_grid_to_zero()
{
  int row_index, column_index;

  set_grid_to_zero();

  for ( row_index = 0; row_index < NUMBER_OF_ROWS; ++row_index ) {
    for ( column_index = 0; column_index < NUMBER_OF_COLUMNS;
                             ++column_index ) {
      CU_ASSERT( game.grid[row_index][column_index] == ZERO );
    }
  }
}

void testSamePositionsInGrid()
{
  PositionInGrid left = {5,4};
  PositionInGrid right = {1,2};
  CU_ASSERT_TRUE( samePositionsInGrid(left,left) );
  CU_ASSERT_FALSE( samePositionsInGrid(left,right) );

}
*/


//////////////////////////////////////////////////////////////////////////////
// Tetrominos suite tests
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Piece suite tests
//////////////////////////////////////////////////////////////////////////////


void testPieceMoveToLeft()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedLeftPiece = {{5,2},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};
  pieceMoveToLeft(&piece);
  
  CU_ASSERT( samePieces(piece,expectedLeftPiece) );
}

void testPieceMoveToRight()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedRightPiece = {{5,3},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,2},TETROMINO_I,ANGLE_0};
  pieceMoveToRight(&piece);
  
  CU_ASSERT( samePieces(piece,expectedRightPiece) );
}

void testPieceMoveToBottom()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedBottomPiece = {{6,3},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};
  pieceMoveToBottom(&piece);
  
  CU_ASSERT( samePieces(piece,expectedBottomPiece) );
}

void testPieceRotateClockwise()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedPiece0 = {{5,3},TETROMINO_I,ANGLE_0};
  Piece expectedPiece90 = {{5,3},TETROMINO_I,ANGLE_90};
  Piece expectedPiece180 = {{5,3},TETROMINO_I,ANGLE_180};
  Piece expectedPiece270 = {{5,3},TETROMINO_I,ANGLE_270};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece90) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece180) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece270) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece0) );
}


//////////////////////////////////////////////////////////////////////////////
// Game suite tests
//////////////////////////////////////////////////////////////////////////////


void test_game_new_destroy()
{
    // Create a grid.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);

    // Create a game.
    Game* game = gameNew(grid, tetrominosCollection);

    // Destroy the game.
    gameDestroy(game);
}


//////////////////////////////////////////////////////////////////////////////
// Functional suite tests
//////////////////////////////////////////////////////////////////////////////

void testRealGame()
{
    unsigned int numberOfRows = 20;
    unsigned int numberOfColumns = 10;
    Game* game = gameNew(numberOfRows, numberOfColumns);

    CU_ASSERT(game->piece->tetromino.type == TETROMINO_SRS_J)

    gameNewPiece(game);
    CU_ASSERT(game->piece->tetromino.type == TETROMINO_SRS_L)

    gameNewPiece(game);
    CU_ASSERT(game->piece->tetromino.type == TETROMINO_SRS_J)

    gameNewPiece(game);
    CU_ASSERT(game->piece->tetromino.type == TETROMINO_SRS_L)

    gameDestroy(game);
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
  CU_pSuite suiteTetromino = NULL;
  CU_pSuite suitePiece = NULL;
  CU_pSuite suitePoint = NULL;
  CU_pSuite Suite_grid = NULL;
  CU_pSuite suiteFunctional = NULL;


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create Grid test suite */
   ADD_SUITE_TO_REGISTRY(Suite_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_new_destroy)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_set_get_cell)
   ADD_TEST_TO_SUITE(Suite_grid,testPiecePositionInGrid)
   ADD_TEST_TO_SUITE(Suite_grid,testGridSetCellsWithPiece)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGrid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGridAndIsVoid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCanSetCellsWithPiece)
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_row_to_zero)*/
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_grid_to_zero)*/

   /* Create Tetromino test suite */
   /*ADD_SUITE_TO_REGISTRY(suiteTetromino)*/

   /* Create Piece test suite */
   ADD_SUITE_TO_REGISTRY(suitePiece )
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToLeft)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToRight)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToBottom)
   ADD_TEST_TO_SUITE(suitePiece, testPieceRotateClockwise)

   /* Create functional test suite */
   ADD_SUITE_TO_REGISTRY(suiteFunctional)
   ADD_TEST_TO_SUITE(suiteFunctional, testRealGame)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   unsigned int number_of_tests_failed = CU_get_number_of_tests_failed();
   CU_cleanup_registry();

   return number_of_tests_failed;
}
