/*
  * Calculate value of the given function.
  * Select 3 digits {3, 5, 6} from the function output and display them in different counting systems: binary, ocatal, hexadecimal.
*/

#include <stdio.h>
#include <math.h>


int main(void)
{
  /* Domain */
  double x = 1.2;

  /* Result of the mathematical function */
  double doMath(double);
  double value = doMath(x);

  /* If the mathematical function resulted in non-number value, it can't be proceeded, because it doesn't have any digits to show. */
  if (value == NAN) return -1;

  void showValues(double);
  showValues(value);
  
  return 0;
}


/* Calculate a mathematical function */
double doMath(double x) {
  double log1 = log(x);

  /* NAN exception */
  if (isnan(log1)) return NAN;

  /* Real value */
  return 5 / (3 + pow(log1 / log(10), 2));
}


unsigned short int selectDigit(double n, int k) {

  /* Format number into scientific notation without maintaining the powerset e.g. abc.def --> a.bcdef * 10^0  <=> a.bcdef */
  while (n < 0)
    n *= 10;
  while (n > 10)
    n /= 10;

  /* Transform from form a.bcdef into a.bcdef * 10^(k-1) e.g. for the first digit it is a.bcdef * 10^0; for the fifth, a.bcdef * 10^4 */
  for (int i = 0; i < k - 1; i++)
    n *= 10;

  /* Cast n into integer; return wanted digit e.g. (a.bcdef * 10^0) % 10 = a; (a.bcdef * 10^4) % 10 = e */
  return (int)n % 10;
}


/* If n is even - return 0; otherwise - return 1 */
_Bool isEven(int n) {
  return n % 2;
}


/* Convert an integer to binary form and print it to stdout */
void decToBin(unsigned long int n)
{
  /* Remainders of division (n % 2) */
  int remainder[65];
  /* Current index */
  int i = 0;
  
  do {
    remainder[i] = isEven(n);
    i++;
  } while ((n /= 2) > 0);

  /* Determine how many zeros to add to remainder to maintain format in eights with zeros in the beginning */
  while(i % 8)
  {
    remainder[i] = 0;
    i++;
  }

  /* Binary form of n */
  char bin[65];
  /* Flip remainder. Add '0' to every integer so it becomes it's corresponding character */
  for (int j = 0; j < i; j++)
    bin[j] = remainder[i - j - 1] + '0';

  /* End as string */
  bin[i] = '\0';
  /* Print formatted verion */
  printf("%10s", bin); 
}

/* Show selected digits of a given value in bin, oct, hex */
void showValues(double val) {

  /* Number of digit to choose from val (from left) */
  unsigned short digitPlace[] = { 3, 5, 6 };
  /* Chosen digits */
  unsigned short digits[3];

  /* Choose digits from val */
  for (int i = 0; i < 3; i++) {
    digits[i] = selectDigit(val, digitPlace[i]);
  }

  /* Full value */
  printf("%10s%20.12f\n","Value:", val);

  /* Counting system */
  printf("%10s%10s%10s\n", "bin", "oct", "hex");
  
  for (int i = 0; i < sizeof(digitPlace) / sizeof(short); i++)
  {
    /* As bin */
    decToBin(digits[i]);
    /* As oct */
    printf("%10o", digits[i]);
    /* As hex */
    printf("%10X", digits[i]);

    printf("\n");
  }
}