#include "rgb_color.h"

bool sameColors(RGBColor const left, RGBColor const right)
{
  return (left.red == right.red) &&
         (left.green == right.green) &&
         (left.blue == right.blue);
}

