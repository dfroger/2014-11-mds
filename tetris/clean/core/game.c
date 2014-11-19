#include <stdlib.h>
#include <string.h>

#include "game.h"
#include <time.h>

static void gameNewPiece(Game* game)
{
    TetrominoType type = rand() % game->tetrominosCollection->numberOfTetrominos;
    game->piece->tetromino = game->tetrominosCollection->tetrominos[type];
    gridSetCellsWithPiece(game->grid, game->piece, game->piece->tetromino.type);
}

Game* gameNew(Grid* grid, TetrominosCollection* tetrominosCollection)
{
    srand(time(NULL));
    Game* game = (Game*) malloc(sizeof(Game));
    game->grid = grid;
    game->tetrominosCollection = tetrominosCollection;

    // Initialize piece
    game->piece = (Piece*) malloc(sizeof(Piece));
    game->piece->topLeftCorner.rowIndex = 0;
    game->piece->topLeftCorner.columnIndex = (grid->numberOfColumns - 
                                              TETROMINO_GRID_SIZE)/2;
    game->piece->angle = ANGLE_0;
    gameNewPiece(game);

    // Initialize pieceMovedOrRotated
    game->pieceMovedOrRotated = (Piece*) malloc(sizeof(Piece));
    memcpy(game->pieceMovedOrRotated, game->piece, sizeof(Piece));

    return game;
}

void gameDestroy(Game* game)
{
    free(game);
}

GameResult gameMoveRight(Game* game)
{
    pieceMoveToRight(game->pieceMovedOrRotated);

    PositionInGrid pos = piecePositionInGrid(game->piece,0);

    // Remove old piece from grid.
    gridSetCellsWithPiece(game->grid, 
                          game->piece,
                          TETROMINO_VOID);

    if (gridCanSetCellsWithPiece(game->grid, game->pieceMovedOrRotated)) {
        // Add new piece to grid.
        gridSetCellsWithPiece(game->grid, 
                              game->pieceMovedOrRotated,
                              game->pieceMovedOrRotated->tetromino.type);

        // Update old piece with new.
        memcpy(game->piece, game->pieceMovedOrRotated, sizeof(Piece));

        return PieceMovedOrRotated;

    } else {
        // Restaure old piece to grid.
        gridSetCellsWithPiece(game->grid, 
                              game->piece,
                              game->piece->tetromino.type);

        // Update new piece with old.
        memcpy(game->pieceMovedOrRotated, game->piece, sizeof(Piece));

        return PieceFailedToMoveOrRotate;
    }
}
