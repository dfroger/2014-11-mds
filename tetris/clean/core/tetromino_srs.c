#include <stdlib.h>
#include <string.h>

#include "tetromino_srs.h"

static unsigned int numberOfTetrominosSRS = 2;

static TetrominoAllRotations tetrominoIAllRotations = {
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
};

static TetrominoAllRotations tetrominoOAllRotations = {
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {1,2} }
};

static Tetromino tetrominoI;
static Tetromino tetrominoO;

TetrominosCollection* getTetrominosCollectionSRS()
{
    tetrominoI.color = RED;
    tetrominoI.type = TETROMINO_SRS_I;
    memcpy(tetrominoI.allRotations, tetrominoIAllRotations, sizeof(TetrominoAllRotations));

    tetrominoO.color = BLUE;
    tetrominoO.type = TETROMINO_SRS_O;
    memcpy(tetrominoO.allRotations, tetrominoOAllRotations, sizeof(TetrominoAllRotations));

    TetrominosCollection* coll = (TetrominosCollection*) malloc(sizeof(TetrominosCollection));
    coll->numberOfTetrominos = numberOfTetrominosSRS; 
    coll->tetrominos = (Tetromino*) malloc(sizeof(Tetromino) * numberOfTetrominosSRS);
    memcpy(coll->tetrominos+TETROMINO_SRS_I, &tetrominoI, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_O, &tetrominoO, sizeof(Tetromino));

    return coll;
}
