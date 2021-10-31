#include "math.h"

#include "decToBin.h"

/*
  * Do a mathematical function
  * Parameter: value as domain
*/
double doMath(double x) {
  double log1 = log(x);
  if (isnan(log1)) return NAN;
  return 5 / (3 + pow(log1 / log(10), 2));
}

/*
  * Select k-th digit from number n
  * Parameters: number, digit number
*/
unsigned short int selectDigit(double n, int k) {

  // Format number into scientific notation
  // without maintaining the powerset
  // e.g. abc.def --> a.bcdef * 10^0  <=> a.bcdef
  while (n < 0)
    n *= 10;
  while (n > 10)
    n /= 10;

  // Transform from form a.bcdef into a.bcdef * 10^(k-1)
  // e.g. for the first digit it is a.bcdef * 10^0
  // for the fifth, a.bcdef * 10^4
  for (int i = 0; i < k - 1; i++)
    n *= 10;

  // Cast n into integer; return wanted digit
  // e.g. (a.bcdef * 10^0) % 10 = a
  // (a.bcdef * 10^4) % 10 = e
  return (int)n % 10;
}

/*
  * Show a value in various counting systems:
  * In bin, oct and hex
  * Parameter: value
*/
void showValues(double val) {

  // Number of digit to choose from val (from left)
  unsigned short int digitPlace[] = { 3, 5, 6 };
  // Chosen digits
  unsigned short int digits[3];

  // Choose digits from val
  for (int i = 0; i < 3; i++) {
    digits[i] = selectDigit(val, digitPlace[i]);
  }

  // Full value
  printf("%10s%20.12f\n","Value:", val);

  // Counting system
  printf("%10s%10s%10s%10s\n", "bin", "oct", "dec", "hex");

  extern void decToBin(unsigned long int);
  
  for (int i = 0; i < 3; i++)
  {
    // As bin
    decToBin(digits[i]);
    // As oct
    printf("%10o", digits[i]);
    // As dec
    printf("%10i", digits[i]);
    // As hex
    printf("%10X", digits[i]);

    printf("\n");
  }
}