#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <stdbool.h>

#include "rgb_color.h"
#include "positionInGrid.h"

#define NUMBER_OF_SQUARES 4
#define NUMBER_OF_TETROMINO_ROTATIONS 4

typedef PositionInGrid TetrominoRotation[NUMBER_OF_SQUARES];

struct tetromino 
{
  RGBColor color;
  TetrominoRotation allRotations[NUMBER_OF_TETROMINO_ROTATIONS];
};
typedef struct tetromino Tetromino;

extern Tetromino const TETROMINO_I;

enum RotationAngle { ANGLE_0=0, ANGLE_90=1, ANGLE_180=2, ANGLE_270=3 };

bool sameTetrominos(Tetromino const left, Tetromino const right);

#endif