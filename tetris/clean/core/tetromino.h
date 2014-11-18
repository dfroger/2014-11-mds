#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <stdbool.h>
#include <stddef.h>

#include "rgb_color.h"
#include "positionInGrid.h"

#define NUMBER_OF_SQUARES 4
#define NUMBER_OF_TETROMINO_ROTATIONS 4

typedef unsigned int TetrominoType;

typedef PositionInGrid TetrominoRotation[NUMBER_OF_SQUARES];
typedef TetrominoRotation TetrominoAllRotations[NUMBER_OF_TETROMINO_ROTATIONS];

enum TetrominoRotationAngle { ANGLE_0=0, ANGLE_90=1, ANGLE_180=2, ANGLE_270=3 };

typedef struct tetromino 
{
  RGBColor color;
  TetrominoType type;
  TetrominoAllRotations allRotations;
} Tetromino;

typedef struct tetromino_collection
{
    unsigned int numberOfTetrominos;
    unsigned int gridSize;
    Tetromino* tetrominos;
} TetrominosCollection;

void tetrominosCollectionDestroy(TetrominosCollection* coll);

#endif
