#include "handleConvertions.h"

int main(void)
{

  double x = 1.2; // Value as domain

  extern double doMath(double);
  extern void showValues(double);

  double funcVal = doMath(x); // Math function result
  if (funcVal == NAN) return -1; // Handle NAN exception
  
  showValues(funcVal);
  
  return 0;
}