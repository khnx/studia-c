/*
  * Generate matrix 10x10 of random numbers;
  * Save it to a txt file
  * Sort the matrix regarding each column's elements' values
  * Append sorted results to the file
*/

#include "main.h"

int main(void)
{
  double matrix[10][10]; // Matrix 10x10 of random numbers
  randomNumbersMatrix(matrix);

  saveMatrixToFile(
    matrix,
    "results.txt",
    "w",
    "Matrix 10x10 of random numbers:"
  );

  sortColumns(matrix);

  saveMatrixToFile(
    matrix,
    "results.txt",
    "a",
    "Matrix 10x10 of numbers sorted in descending order:"
  );

  showMatrix(matrix, 10);

  return 0;
}


void saveMatrixToFile(
                    double matrix[][10],
                    char *filename,
                    char *mode,
                    char *msg) {
  // File pointer
  FILE *file = fopen(filename, mode);

  if (file != NULL) {
    // Matrix entires
    fprintf(file, "%s", msg);
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++)
        fprintf(file, "%6.1lf", matrix[i][j]);
      fprintf(file, "\n");
    }
    fprintf(file, "\n");
  }

  fclose(file);
}


void randomNumbersMatrix(double matrix[][10])
{
  srand(SEED);

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrix[i][j] = rand() % 100;
}


void exch(double v[], int n, int m)
{
  double temp = v[n];
  v[n] = v[m];
  v[m] = temp;
}


short compare(double a, double b) {
  return (a - b) > 0;
}


int partition(double v[], int lo, int hi) {
  int i = lo;
  int j = hi+1;
  double item = v[lo];
  
  while (1) {
    while (compare(v[++i], item)) if (i == hi) break;
    while (compare(item, v[--j])) if (j == lo) break;
    if (i >= j) break;
    exch(v, i, j);
  }
  exch(v, lo, j);
  return j;
}


void quicksort(double v[], int lo, int hi) {
  if (hi <= lo) return;
  int j = partition(v, lo, hi);
  quicksort(v, lo, j-1);
  quicksort(v, lo+1, hi);
}


void sortColumns(double matrix[][10])
{
  double col[10]; // column

  for (int i = 0; i < 10; i++) {
    int k = 0; // counter for column

    for (int j = 0; j < 10; j++)
      col[k++] = matrix[j][i]; // write from matrix to col

    quicksort(col, 0, 9);
    
    k = 0; // reset k
    for (int j = 0; j < 10; j++)
      matrix[j][i] = col[k++]; // write from column to matrix
  }
}