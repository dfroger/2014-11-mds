#include <stdlib.h>

#include "game.h"

static void gameNewPiece(Game* game)
{
    TetrominoType type = rand() % game->tetrominosCollection->numberOfTetrominos;
    game->piece = &game->tetrominosCollection->tetrominos[type];
    gridSetCellsWithPiece(game->grid, game->piece);
}

Game* gameNew(Grid* grid, TetrominosCollection* tetrominosCollection)
{
    srand(time(NULL));
    Game* game = (Game*) malloc(sizeof(Game));
    game->grid = grid;
    game->tetrominosCollection = tetrominosCollection;
    game->piece = (Piece*) malloc(sizeof(Piece));
    gameNewPiece(game);
    return game;
}

void gameDestroy(Game* game)
{
    free(game);
}
