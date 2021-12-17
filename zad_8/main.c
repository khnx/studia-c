/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
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


/* Number of elements of the permutation */
#define NUMBER_OF_LETTERS  6
/* Single permutation */
char P[NUMBER_OF_LETTERS];


/* Exchange values of two elements of an array */
void exch(char v[], int i, int j) {
  char temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}


/* Return true if number if even, false otherwise */
_Bool isEven(int n) { return !(n % 2); }


/* Generate permutations */
void PERM(int m) {
  /* Number of permutation */
  static int noPerm = 1;

  /* Base case - print results */
  if (m == 1) {
  printf("%5i:\t", noPerm++);
    for (int i = 0; i < NUMBER_OF_LETTERS; i++) printf("%5c", P[i]);
  printf("\n");
  } else {
    /* Recursion */
    PERM(m - 1);
    
    /* m-th element swapped with each m-1 */
    for (int i = 0; i < m-1; i++) {
      /* Swap dependent on parity of m (even) */
      if (isEven(m)) exch(P, i, m - 1);
      /* Odd */
      else exch(P, 0, m-1);
      PERM(m - 1);
    }
  }
}


/* Calculate factorial of given number */
long long factorial(int n) {
  if (n < 0) return 0;
  else if (n == 0 || n == 1) return 1;
  return n * factorial(n - 1);
}


int main(void)
{
  for (int i = 0; i < NUMBER_OF_LETTERS; i++) P[i] = i + 'a';
  
  PERM(NUMBER_OF_LETTERS);
  printf("Predicted number of permutations: %lli\n", factorial(NUMBER_OF_LETTERS));

  return 0;
}