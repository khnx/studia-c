/* ***** LIBRARIES ***** */
#include <stdio.h>
#include <math.h>

#include "../utils/utils.c"

/* ***** PROTOTYPES ***** */

/*
  * Do a mathematical function
  * Parameter: value as domain
*/
double doMath(double x);

/*
  * Select k-th digit from number n
  * Parameters: number, digit number
*/
unsigned short int selectDigit(double n, int k);

/*
  * Show a value in various counting systems:
  * In bin, oct and hex
  * Parameter: value
*/
void showValues(double val);

/*
  * Convert decimal integer to binary form
  * Integer must be positive
  * Parameters:
  * integer (dec)
*/
void decToBin(unsigned long int n);