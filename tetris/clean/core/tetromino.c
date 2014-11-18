#include <stdlib.h>

#include "tetromino.h"

void tetrominosCollectionDestroy(TetrominosCollection* coll)
{
    free(coll->tetrominos);
    free(coll);
}
