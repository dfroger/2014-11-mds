#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

#include "piece.h"
#include "tetromino_srs.h"
#include "grid.h"

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
    unsigned int numberOfRows = 16;
    unsigned int numberOfColumns = 12;
    Grid* grid = grid_new(numberOfRows, numberOfColumns);
    grid_destroy(grid);
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

void testPieceRotate()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedPiece0 = {{5,3},TETROMINO_I,ANGLE_0};
  Piece expectedPiece90 = {{5,3},TETROMINO_I,ANGLE_90};
  Piece expectedPiece180 = {{5,3},TETROMINO_I,ANGLE_180};
  Piece expectedPiece270 = {{5,3},TETROMINO_I,ANGLE_270};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};

  pieceRotate(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece90) );

  pieceRotate(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece180) );

  pieceRotate(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece270) );

  pieceRotate(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece0) );
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


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create Grid test suite */
   ADD_SUITE_TO_REGISTRY(Suite_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_new_destroy)
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_row_to_zero)*/
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_grid_to_zero)*/

   /* Create Tetromino test suite */
   /*ADD_SUITE_TO_REGISTRY(suiteTetromino)*/

   /* Create Piece test suite */
   ADD_SUITE_TO_REGISTRY(suitePiece )
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToLeft)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToRight)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToBottom)
   ADD_TEST_TO_SUITE(suitePiece, testPieceRotate)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   unsigned int number_of_tests_failed = CU_get_number_of_tests_failed();
   CU_cleanup_registry();

   return number_of_tests_failed;
}
