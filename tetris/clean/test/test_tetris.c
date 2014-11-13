
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

bool testSamePositionsInGrid()
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


void testPieceCopyToLeft()
{
  Piece rightPiece = {{5,3},TETROMINO_I,ANGLE_0};
  Piece expectedLeftPiece = {{5,2},TETROMINO_I,ANGLE_0};
  Piece actualLeftPiece;
  pieceCopyToLeft(rightPiece,&actualLeftPiece);
  CU_ASSERT( samePieces(actualLeftPiece,expectedLeftPiece) );
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
   Suite_grid = CU_add_suite("Suite_grid", init_suite, clean_suite);
   if ( Suite_grid == NULL ) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(Suite_grid, "test of set_row_to_zero()", test_set_row_to_zero)) ||
       (NULL == CU_add_test(Suite_grid, "test of set_grid_to_zero()", test_set_grid_to_zero)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Create Color test suite */
   suiteColor = CU_add_suite("suiteColor", init_suite, clean_suite);
   if ( suiteColor == NULL ) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ( ( CU_add_test(suiteColor, "testSameColors()", testSameColors) == NULL ) )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Create Tetromino test suite */
   suiteTetromino = CU_add_suite("suiteTetromino", init_suite, clean_suite);
   if ( suiteTetromino == NULL ) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ( ( CU_add_test(suiteTetromino, "testSameTetraminos()", testSameTetraminos) == NULL ) )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Create Piece test suite */
   suitePiece = CU_add_suite("suitePiece", init_suite, clean_suite);
   if ( suitePiece == NULL ) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ( ( CU_add_test(suitePiece, "testPieceCopyToLeft()", testPieceCopyToLeft) == NULL ) )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Create Point test suite */
   suitePoint = CU_add_suite("suitePoint", init_suite, clean_suite);
   if ( suitePoint == NULL ) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ( ( CU_add_test(suitePoint, "test_rotate90()", test_rotate90) == NULL ) )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

