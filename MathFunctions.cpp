#include "MathFunctions.h"

unsigned int getNewID()
{
  static unsigned int id = 0;
  id++;
  return id;
}

bool valueInRange(double value, double min, double max)
{
  return (value >= min) && (value <= max);
}