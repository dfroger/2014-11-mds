#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "tetromino_srs.h"
#include <time.h>

#ifdef WITH_MOCK
static size_t numberOfNoMoreRandomTetrominoType = 2;
static size_t noMoreRandomTetrominoTypeIndex = 0;
static TetrominoType noMoreRandomTetrominoType[2] = {TETROMINO_SRS_J, TETROMINO_SRS_L};
static TetrominoType getRandomTetrominoType()
{
    TetrominoType tetrominoType = noMoreRandomTetrominoType[noMoreRandomTetrominoTypeIndex];
    noMoreRandomTetrominoTypeIndex = (noMoreRandomTetrominoTypeIndex + 1) % 
                                     numberOfNoMoreRandomTetrominoType;
    return tetrominoType;
}
#else
static TetrominoType getRandomTetrominoType()
{
    return TetrominoType type = rand() % game->tetrominosCollection->numberOfTetrominos;
}
#endif

void gameNewPiece(Game* game)
{
    game->piece->topLeftCorner.rowIndex = 0;
    game->piece->topLeftCorner.columnIndex = (game->grid->numberOfColumns - 
                                              TETROMINO_GRID_SIZE)/2;
    game->piece->angle = ANGLE_0;
    
    TetrominoType type = getRandomTetrominoType();
    game->piece->tetromino = game->tetrominosCollection->tetrominos[type];
    
    gridSetCellsWithPiece(game->grid, game->piece, game->piece->tetromino.type);
}

Game* gameNew(size_t numberOfRows, size_t numberOfColumns)
{
    srand(time(NULL));
    Game* game = (Game*) malloc(sizeof(Game));
    game->grid = grid_new(numberOfRows, numberOfColumns);
    game->tetrominosCollection = getTetrominosCollectionSRS();

    // Initialize piece
    game->piece = (Piece*) malloc(sizeof(Piece));
    gameNewPiece(game);

    return game;
}

void gameDestroy(Game* game)
{
    free(game->tetrominosCollection);
    free(game->piece);
    grid_destroy(game->grid);
    free(game);
}

bool gameTryToMoveRight(Game* game)
{
  return  gameTryToMove(game,pieceMoveToRight,pieceMoveToLeft);
}

bool gameTryToMoveLeft(Game* game)
{
  return gameTryToMove(game,pieceMoveToLeft,pieceMoveToRight);
}

bool gameTryToMoveBottom(Game* game)
{
  return gameTryToMove(game,pieceMoveToBottom,pieceMoveToTop);
}

bool gameTryToRotateClockwise(Game* game)
{
  return gameTryToMove(game,pieceRotateClockwise,pieceRotateCounterClockwise);
}

bool gameTryToMove(Game* game,void (*move)(Piece*),void (*unmove)(Piece*))
{
  bool managedToMove = true;

  gridSetCellsWithPiece(game->grid, 
                        game->piece,
                        TETROMINO_VOID);

  move(game->piece);

  if (! gridCanSetCellsWithPiece(game->grid, game->piece)) {
      managedToMove = false;
      unmove(game->piece);
  }

  gridSetCellsWithPiece(game->grid, 
                        game->piece,
                        game->piece->tetromino.type);

  return managedToMove;
}


