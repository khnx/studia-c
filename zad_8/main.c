/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @brief Recursive Heap's Algorithm
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 */

/*
  * Generate permutations considering letters with 6 elements in a set
  * Permutation algorithm: 1.11
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Number of elements of the permutation */
#define NUMBER_OF_LETTERS  6
/* Single permutation */
char P[NUMBER_OF_LETTERS];

/* Colors */
#define C_BRED "\e[1;31m"
#define C_RESET "\e[0m"
#define C_BYEL "\e[1;33m"


/* Exchange values of two elements of an array */
void exch(char v[], int i, int j) {
  char temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}


/* Return true if number if even. */
bool isEven(int n) { return !(n % 2); }


/* Generate permutations. m is the number of initial elements of the permutation set. m = NUMBER_OF_LETTERS initially. Later, m < NUMBER_OF_LETTERS. Performs permutations by calling itself with m-th element unaltered and then m-1 times with m-th element exchanged for one of initial m-1 elements. */
void PERM(int m) {
  /* Number of permutation */
  static int noPerm = 1;
  /* Value of m and i on previous iteration. For colors. */
  static int mval = -1;
  static int ival = -1;

  /* Base case - print results */
  if (m == 1) {
    printf("%5i:\t", noPerm++);
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) {
      /* Highlight transpositions. */
      if (i == mval)
        printf("%s%5c%s", C_BRED, P[i], C_RESET);
      else if (i == ival)
        printf("%s%5c%s", C_BYEL, P[i], C_RESET);
      else
        printf("%5c", P[i]);
    }
    printf("\n");
  } else {
    PERM(m - 1);
    
    /* m-th element swapped with each m-1 */
    for (int i = 0; i < m-1; i++) {
      /* Swap dependent on parity of m (even) */
      if (isEven(m))
        exch(P, i, m - 1);
      /* Odd */
      else
        exch(P, 0, m-1);
      mval = m - 1;
      ival = i;
      PERM(m - 1);
    }
  }
}


/* Calculate factorial of given number */
size_t factorial(size_t n) {
  if (n < 0) return 0;
  else if (n == 0 || n == 1) return 1;
  return n * factorial(n - 1);
}


int main( void ) {
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) P[i] = i + 'a';
  
  PERM(NUMBER_OF_LETTERS);
  printf("Predicted number of permutations: %zu\n", factorial(NUMBER_OF_LETTERS));

  exit( EXIT_SUCCESS );
}