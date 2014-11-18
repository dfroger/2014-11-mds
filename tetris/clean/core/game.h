#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "grid.h"

typedef struct game {
    Grid* grid;
    TetrominosCollection* tetrominosCollection;
} Game;

Game* game_new();
void game_destroy(Game* game);

#endif
