#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <stddef.h>
#include <stdbool.h>
#include "tetromino.h"

#define SPACE_DIMENSION 2
//#define NUMBER_OF_TETROMINO_TYPES 7


typedef struct piece Piece;
struct piece
{
  PositionInGrid topLeftCorner;
  Tetromino tetromino;
  size_t angle;
};

void pieceCopyToLeft(Piece const original, Piece * copy);
bool samePieces(Piece const left, Piece const right);

#endif
