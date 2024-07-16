#include <stdio.h>

#include "calculator.h"

double
add(double x, double y)
{
  return x + y;
}

double
subtract(double x, double y)
{
  return x - y;
}

double
multiply(double x, double y)
{
  return x * y;
}

double
divide(double x, double y)
{
  if (y != 0) {
    return x / y;
  } else {
    puts("Error: division by zero\n");
    return 0.0;
  }
}
