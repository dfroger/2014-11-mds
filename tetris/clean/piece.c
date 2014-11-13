#include "piece.h"

void pieceMoveToLeft(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

bool samePieces(Piece const left, Piece const right)
{
  return samePositionsInGrid(left.topLeftCorner,right.topLeftCorner) &&
         sameTetrominos(left.tetromino,right.tetromino) &&
         (left.angle == right.angle);
  
}
