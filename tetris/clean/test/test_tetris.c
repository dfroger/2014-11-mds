
/* CUnit files */
#include "CUnit/Basic.h"

/* Tetris files */
#include "grid.h"
#include "point.h"
#include "piece.h"
/* Standard library files */
#include <stdio.h>
#include <string.h>

static size_t random_row_index;
static size_t const ZERO = 0;

/* Suite initialization */
int init_suite()
{
   random_row_index = rand() % NUMBER_OF_ROWS;
   return 0;
}

/* Suite termination */
int clean_suite()
{
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


//////////////////////////////////////////////////////////////////////////////
// Colors suite tests
//////////////////////////////////////////////////////////////////////////////


void testSameColors()
{
  RGBColor red = RED;
  CU_ASSERT_TRUE( sameColors(WHITE,WHITE) );
  CU_ASSERT_FALSE( sameColors(WHITE,red) );
}


//////////////////////////////////////////////////////////////////////////////
// Tetrominos suite tests
//////////////////////////////////////////////////////////////////////////////


void testSameTetraminos()
{
  CU_ASSERT( sameTetrominos(TETROMINO_I,TETROMINO_I) );
}


//////////////////////////////////////////////////////////////////////////////
// Piece suite tests
//////////////////////////////////////////////////////////////////////////////


void testPieceMoveToLeft()
{
  Piece expectedLeftPiece = {{5,2},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};
  pieceMoveToLeft(&piece);
  
  CU_ASSERT( samePieces(piece,expectedLeftPiece) );
}

void testPieceMoveToRight()
{
  Piece expectedRightPiece = {{5,3},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,2},TETROMINO_I,ANGLE_0};
  pieceMoveToRight(&piece);
  
  CU_ASSERT( samePieces(piece,expectedRightPiece) );
}


//////////////////////////////////////////////////////////////////////////////
// Deprecated suite tests
//////////////////////////////////////////////////////////////////////////////


void test_rotate90()
{
  Point const center = {3,1};
  Point point = {4,1};

  Point point0 = point;
  Point point90 = {3,2};
  Point point180 = {2,1};
  Point point270 = {3,0};
  
  rotate90(center,&point);
  CU_ASSERT( samePoints(point,point90) );
  
  rotate90(center,&point);
  CU_ASSERT( samePoints(point,point180) );
  
  rotate90(center,&point);
  CU_ASSERT( samePoints(point,point270) );
  
  rotate90(center,&point);
  CU_ASSERT( samePoints(point,point0) );
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
  CU_pSuite suiteColor = NULL;
  CU_pSuite suiteTetromino = NULL;
  CU_pSuite suitePiece = NULL;
  CU_pSuite suitePoint = NULL;
  CU_pSuite Suite_grid = NULL;


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create Grid test suite */
   ADD_SUITE_TO_REGISTRY(Suite_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_set_row_to_zero)
   ADD_TEST_TO_SUITE(Suite_grid,test_set_grid_to_zero)

   /* Create Color test suite */
   ADD_SUITE_TO_REGISTRY(suiteColor)
   ADD_TEST_TO_SUITE(suiteColor, testSameColors)

   /* Create Tetromino test suite */
   ADD_SUITE_TO_REGISTRY(suiteTetromino)
   ADD_TEST_TO_SUITE(suiteTetromino, testSameTetraminos)

   /* Create Piece test suite */
   ADD_SUITE_TO_REGISTRY(suitePiece )
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToLeft)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToRight)

   /* Create Point test suite */
   ADD_SUITE_TO_REGISTRY(suitePoint )
   ADD_TEST_TO_SUITE(suitePoint, test_rotate90)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
