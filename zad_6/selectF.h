#include "math.h"

void show(double arr[][10]) {
  for (int i = 0; i  < 10; i++) {
    for (int j = 0; j < 10; j++)
      printf("%6.f", arr[i][j]);
    printf("\n");
  }
}

/*
  * Select entries from under the main diagonal of arr
  * Parameters: array 2D, array 2D
*/
void selectF(double arr[][10], double diagonal[][10]) {
  int m = 0; // diagonal rows
  int n = 0; // diagonal cols
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i > j) diagonal[m][n] = arr[i][j];
      // Populate with nans (avoid trash values)
      else diagonal[m][n] = NAN;
      n++;
    }
    m++;
    n = 0;
  }
}

/*
  * Select single column from a 2D array
  * Parameters: array 2D, array, col number
*/
void selectCol(double arr[][10], double col[], int n)
{
  int j = 0;
  for (int i = 0; i < 10; i++)
    col[j++] = arr[i][n];
}

/*
  * Select the highest values for each column
  * Return these values in array max
  * Parameters: array 2D, array
*/
void selectHighest(double arr[][10], double max[]) {
  double col[10]; // Placeholder for each column

  for (int i = 0; i < 10; i++) {
    selectCol(arr, col, i); // Select a col
    extern void bubbleSort(double [], int, int);
    bubbleSort(col, 10, 1); // Sort it

    int j = 0;
    while (isnan(col[j])) j++;

    max[i] = col[j]; // Select the highest values
    if (j == 10) max[i] = NAN; // Whole column is NAN
  }
}