#include "stdio.h"

// Utility function
// Check if number is even
int isEven(long int n) { return n % 2; }

/*
  * Convert decimal integer to binary form
  * Integer must be positive
  * Parameters:
  * integer (dec)
*/
void decToBin(unsigned long int n)
{

  int remainder[65]; // Remainders of division (n % 2)
  int i = 0; // Current index
  
  do {
    remainder[i] = isEven(n);
    i++;
  } while ((n /= 2) > 0);

  // Determine how many zeros to add to remainder to maintain format in eights
  // with zeros in the beginning, if needed
  while(i % 8)
  {
    remainder[i] = 0;
    i++;
  }

  char bin[65]; // Binary form of n
  // Flip remainder
  // Add '0' to every integer so it becomes it's corresponding character
  for (int j = 0; j < i; j++)
  { bin[j] = remainder[i - j - 1] + '0'; }

  // End as string
  bin[i] = '\0';

  // Print formatted verion onto the terminal
  printf("%10s", bin);
}