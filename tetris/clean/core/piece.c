#include "piece.h"

void pieceMoveToLeft(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

void pieceMoveToRight(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex++;
}

void pieceMoveToBottom(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex++;
}

void pieceRotate(Piece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+1) % TETROMINO_NUMBER_OF_ROTATIONS;
}

bool samePieces(Piece const left, Piece const right)
{
  return samePositionsInGrid(left.topLeftCorner,right.topLeftCorner) &&
         left.tetromino.type == right.tetromino.type &&
         (left.angle == right.angle);
}
