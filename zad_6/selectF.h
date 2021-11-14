#include <math.h>
#include <stdio.h>

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

void sumRows(double arr[][10], double sums[]) {
  double rowNumber[10];

  for (int i = 0; i < 10; i++) {
    double sum = 0;
    int j = 0;
    for (j; !isnan(arr[i][j]); j++)
      sum += arr[i][j];
    if (j > 0) sums[i] = sum;
    else sums[i] = NAN;
  }
}