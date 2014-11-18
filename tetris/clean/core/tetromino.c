#include "tetromino.h"

Tetromino const TETROMINO_I = {{
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
}};

Tetromino const TETROMINO_O = {{
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} }
}};

bool sameTetrominos(Tetromino const left, Tetromino const right)
{
  // Todo: create a function
  size_t angle, square_index;
  for (angle=ANGLE_0 ; angle <= ANGLE_270; ++angle) {
    for (square_index = 0 ; square_index < NUMBER_OF_SQUARES ; ++square_index) {
        if (! samePositionsInGrid(left.allRotations[angle][square_index],
                                  right.allRotations[angle][square_index]) )
            return false;
    }
  }

  return true;
}
