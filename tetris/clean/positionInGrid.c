#include "positionInGrid.h"

bool samePositionsInGrid(PositionInGrid const left, PositionInGrid const right)
{
  return (left.rowIndex == right.rowIndex) &&
         (left.columnIndex == right.columnIndex);
}

