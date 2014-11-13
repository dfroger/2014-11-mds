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
    toBeRotated->angle = (toBeRotated->angle+1) % NUMBER_OF_TETROMINO_ROTATIONS;
}

bool samePieces(Piece const left, Piece const right)
{
  return samePositionsInGrid(left.topLeftCorner,right.topLeftCorner) &&
         sameTetrominos(left.tetromino,right.tetromino) &&
         (left.angle == right.angle);
  
}
