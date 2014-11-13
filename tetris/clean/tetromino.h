#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include "rgb_color.h"

#define NUMBER_OF_SQUARES 4
#define NUMBER_OF_TETROMINO_ROTATIONS 4

struct positionInGrid
{
  int rowIndex;
  int columnIndex;
};
typedef struct positionInGrid PositionInGrid;

typedef PositionInGrid TetrominoRotation[NUMBER_OF_SQUARES];

struct tetromino 
{
  rgb_color color;
  TetrominoRotation rotations[NUMBER_OF_TETROMINO_ROTATIONS];
};
typedef struct tetromino Tetromino;

extern Tetromino const TETROMINO_I;

enum RotationAngle { ANGLE_0=0, ANGLE_90=1, ANGLE_180=2, ANGLE_270=3 };



#endif
