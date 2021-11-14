#include "main.h"

int main(void)
{
  double x = 1.2; // Value as domain
  double funcVal = doMath(x); // Math function result
  if (funcVal == NAN) return -1; // NAN exception 
  showValues(funcVal);
  
  return 0;
}

double doMath(double x) {
  double log1 = log(x);
  if (isnan(log1)) return NAN;
  return 5 / (3 + pow(log1 / log(10), 2));
}

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

void decToBin(unsigned long int n)
{

  int remainder[65]; // Remainders of division (n % 2)
  int i = 0; // Current index
  
  do {
    remainder[i] = isEven(n);
    i++;
  } while ((n /= 2) > 0);

  // Determine how many zeros to add to remainder to maintain format in eights with zeros in the beginning
  while(i % 8)
  {
    remainder[i] = 0;
    i++;
  }

  char bin[65]; // Binary form of n
  // Flip remainder. Add '0' to every integer so it becomes
  // it's corresponding character
  for (int j = 0; j < i; j++)
    bin[j] = remainder[i - j - 1] + '0';

  bin[i] = '\0'; // End as string
  printf("%10s", bin); // Print formatted verion
}