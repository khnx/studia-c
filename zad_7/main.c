#include "main.h"

int main(void)
{
  double matrix[10][10]; // Matrix 10x10 of random numbers
  generateRandomNumbersMatrix(matrix);
  saveMatrixToFile(matrix, "results.txt");
  sortColumns(matrix);
  showMatrix(matrix, 10);

  return 0;
}

void generateRandomNumbersMatrix(double matrix[][10])
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

void quicksort(double v[], int l, int r)
{
  int i, last;

  if (l >= r) return; // Less than 2 elements
  exch(v, l, (l + r/2));
  last = l;
  for (i = l+1; i<= r; i++)
    if (v[i] < v[l])
      exch(v, ++last, i);
  exch(v, l, last);
  quicksort(v, l, last-1);
  quicksort(v, last+1, r);
}

void sortColumns(double matrix[][10])
{
  double col[10]; // column

  for (int i = 0; i < 10; i++) {
    int k = 0; // counter for column

    for (int j = 0; j < 10; j++)
      col[k++] = matrix[j][i]; // write from matrix to col

    quicksort(col, 0, 10); // sort column
    
    k = 0; // reset k
    for (int j = 0; j < 10; j++)
      matrix[j][i] = col[k++]; // write from column to matrix
  }
}