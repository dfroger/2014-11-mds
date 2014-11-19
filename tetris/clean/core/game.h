#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "grid.h"
#include "piece.h"

typedef struct game {
    Grid* grid;
    Piece* piece;
    TetrominosCollection* tetrominosCollection;
} Game;

Game* gameNew();
void gameDestroy(Game* game);

void gameTryToMove(Game* game, void (*move)(Piece*), void (*unmove)(Piece*));
void gameTryToMoveRight(Game* game);
void gameTryToMoveLeft(Game* game);
void gameTryToMoveBottom(Game* game);
void gameTryToRotateClockwise(Game* game);
//void gameTryToMoveMaximumBottom(Game* game);
//void gameTryToRotate(Game* game);

#endif
