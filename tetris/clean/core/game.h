#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "grid.h"
#include "piece.h"

typedef struct game {
    Grid* grid;
    TetrominosCollection* tetrominosCollection;
} Game;

Game* gameNew();
void gameDestroy(Game* game);

/* Game API we be something like this:
 *
 * enum GameEvent {
 *    PieceMovedOrRotated, 
 *    PieceFailedToMoveOrRotate, 
 *    ZeroRowSuppressed,
 *    OneRowSuppressed,
 *    TwoRowSuppressed,
 *    ThreeRowSuppressed,
 *    FourRowSuppressed,
 *    gameOver
 * }
 *
 * GameEvent game_move_right(Game* game);
 * GameEvent game_move_left(Game* game);
 * GameEvent game_move_bottom(Game* game);
 *
 * unsigned int game_get_score(Game* game);
 *
 * */

/* Temporary, to remove from plublic API:just for testing tetris-gtk */
void gameDemo(Game* game, Piece* piece);

#endif
