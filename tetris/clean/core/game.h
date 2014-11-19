#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "grid.h"
#include "piece.h"

typedef enum {PieceMovedOrRotated, PieceFailedToMoveOrRotate, 
              NextPiece, GameOver} GameResult ;

typedef struct game {
    Grid* grid;
    Piece* piece;
    Piece* pieceMovedOrRotated;
    TetrominosCollection* tetrominosCollection;
} Game;

Game* gameNew();
void gameDestroy(Game* game);

GameResult gameMoveRight(Game* game);
//GameResult gameMoveLeft(Game* game);
//GameResult gameMoveBottom(Game* game);
//GameResult gameMoveMaximumBottom(Game* game);
//GameResult gameRotate(Game* game);

#endif
