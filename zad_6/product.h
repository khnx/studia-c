#include "math.h"

/*
  * Return product value of an array
  * Parameters: array
*/
double product(double arr[]) {
  double p = 1; // Product
  for (int i = 0; i < 10; i++)
    if(!isnan(arr[i]))
      p *= arr[i];
  return p;
}