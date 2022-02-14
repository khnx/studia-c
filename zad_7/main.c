/*
  * Generate matrix 10x10 of random numbers;
  * Save it to a txt file
  * Sort the matrix regarding each column's elements' values, in descending order
  * Append sorted results to the file
*/

#include <stdio.h>
#include <stdlib.h>


/* Generate random numbers from this seed. */
#define SEED 62


void randomNumbersMatrix(int [][10]);
void saveMatrixToFile(int [][10], char *, char *, char *);
void sortColumns(int [][10]);


int main(void) {
  /* Matrix 10x10 of random numbers */
  int matrix[10][10];

  randomNumbersMatrix(matrix);

  /* Save matrix of random values */
  saveMatrixToFile(
    matrix,
    "results.txt",
    "w",
    "Matrix 10x10 of random numbers:\n");

  sortColumns(matrix);

  /* Save matrix of sorted values */
  saveMatrixToFile(
    matrix,
    "results.txt",
    "a",
    "Matrix 10x10 of numbers sorted in descending order:\n");

  return 0;
}


/* Generate a matrix filled with random numbers */
void randomNumbersMatrix(int matrix[][10]) {
  srand(SEED);

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrix[i][j] = rand() % 100;
}


/* Saves specified array to a file. Takes the matrix, file name, mode in which file should be saved (e.g. "r"), message to label the data in the file. */
void saveMatrixToFile(int matrix[][10], char *filename, char *mode, char *msg) {

  FILE *file = fopen(filename, mode);
  if ( file == NULL) {
    perror( "saveMatrixToFile" );
    exit( EXIT_FAILURE );
  }

  /* Matrix entires */
  fprintf(file, "%s", msg);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++)
      fprintf(file, "%6i", matrix[i][j]);
    fprintf(file, "\n");
  }
  fprintf(file, "\n");
  fclose(file);
}


/* Exchange values of two variables of an array */
void exch(int v[], int n, int m) {
  int temp = v[n];
  v[n] = v[m];
  v[m] = temp;
}


/* Return true when first number is greater than the second */
short compare(int a, int b) {
  return (a - b) > 0; // True when a > b
}


/*
  * Logic for quicksort. Performs exchanges in two cases: value on the side of the pivot, where it should be smaller than the piot is higher or vice versa; or new pivot is exchanged with the previous one (because it hasn't been compared yet).
  * Parameters: array to sort, index of a value that should be smaller, index of value that should be higher
*/
int partition(int v[], int lo, int hi) {
  /* Index of an element with higher value than pivot, on the side, where elements' values are ought to be lower */
  int i = lo;
  /* Index of an element with lower value than pivot, on the side, where elements' values are ought to be higher */
  int j = hi+1;
  /* Pivot */
  int item = v[lo];

  while (1) {
    /* Search for the i */
    while (compare(v[++i], item)) if (i == hi) break;
    /* Search for the j */
    while (compare(item, v[--j])) if (j == lo) break;
    /* End, when indexes meet */
    if (i >= j) break;
    /* Exchange values of elements standing on the wrong side of the pivot */
    exch(v, i, j);
  }

  /* Exchange pivot with an element with index j */
  exch(v, lo, j);
  /* New pivot */
  return j;
}


/* Sort an array in descending order; takes array, lowest and highest indexes of the subarray that should be sorted. */
void quicksort(int v[], int lo, int hi) {
  /* Base case */
  if (hi <= lo) return;
  /* New pivot */
  int j = partition(v, lo, hi);
  /* Sort left side */
  quicksort(v, lo, j-1);
  /* Sort right side */
  quicksort(v, lo+1, hi);
}


/* Sort the matrix regarding each column's elements' values, in descending order */
void sortColumns(int matrix[][10]) {
  /* Column */
  int col[10];

  for (int i = 0; i < 10; i++) {
    /* Index for the column each entry */
    int k = 0;

    /* Extract single column */
    for (int j = 0; j < 10; j++)
      /* Write from matrix to col */
      col[k++] = matrix[j][i];

    quicksort(col, 0, 9);
    
    /* Reset k */
    k = 0;
    for (int j = 0; j < 10; j++)
      /* Write from column to matrix */
      matrix[j][i] = col[k++];
  }
}
