#include <stdlib.h>

#include "game.h"

Game* game_new(Grid* grid, TetrominosCollection* tetrominosCollection)
{
    Game* game = (Game*) malloc(sizeof(Game));
    game->grid = grid;
    game->tetrominosCollection = tetrominosCollection;
}

void game_destroy(Game* game)
{
    free(game);
}
