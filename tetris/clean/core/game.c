#include <stdlib.h>

#include "game.h"

static void gameDrawPiece(Game* game, Piece* piece)
{
    unsigned squareIndex;
    PositionInGrid pos;

    for (squareIndex = 0 ; 
         squareIndex < TETROMINO_NUMBER_OF_SQUARES ;
         squareIndex++)
    {
        pos.rowIndex = piece->topLeftCorner.rowIndex + 
           piece->tetromino.allRotations[piece->angle][squareIndex].rowIndex;

        pos.columnIndex = piece->topLeftCorner.columnIndex + 
           piece->tetromino.allRotations[piece->angle][squareIndex].columnIndex;

        grid_set_cell(game->grid, pos, piece->tetromino.type);
    }
}

Game* gameNew(Grid* grid, TetrominosCollection* tetrominosCollection)
{
    Game* game = (Game*) malloc(sizeof(Game));
    game->grid = grid;
    game->tetrominosCollection = tetrominosCollection;
    return game;
}

void gameDestroy(Game* game)
{
    free(game);
}

void gameDemo(Game* game, Piece* piece)
{
    grid_clear(game->grid);
    gameDrawPiece(game, piece);
}
