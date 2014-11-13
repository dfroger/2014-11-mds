#include "tetromino.h"

Tetromino const TETROMINO_I = {
  RED, {
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
} };

bool sameTetrominos(Tetromino const left, Tetromino const right)
{
  if (! sameColors(left.color, right.color))
    return false;

  return true;
}
