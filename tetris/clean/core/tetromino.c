#include <stdlib.h>

#include "tetromino.h"

TetrominoType const TETROMINO_VOID = 100;

void tetrominosCollectionDestroy(TetrominosCollection* coll)
{
    free(coll->tetrominos);
    free(coll);
}
