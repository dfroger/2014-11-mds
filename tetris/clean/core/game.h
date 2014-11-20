#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "grid.h"
#include "piece.h"

typedef struct game {
    Grid* grid;
    Piece* piece;
    TetrominosCollection* tetrominosCollection;
} Game;

bool gameNewPiece(Game* game);
Game* gameNew(size_t numberOfRows, size_t numberOfColumns);
void gameDestroy(Game* game);

bool gameTryToMove(Game* game, void (*move)(Piece*), void (*unmove)(Piece*));
bool gameTryToMoveRight(Game* game);
bool gameTryToMoveLeft(Game* game);
bool gameTryToMoveBottom(Game* game);
bool gameTryToRotateClockwise(Game* game);

#endif
