#include <stdio.h>

#include "addOns.h" // Custom libraries

int main(void)
{

  double matrix[10][10]; // Space for matrix 10x10

  importMatrix(matrix);
  sortMatrix(matrix);

  double diagonal[10][10];
  selectF(matrix, diagonal);
  double rowsSum[10];
  sumRows(diagonal, rowsSum);
  double prod = product(rowsSum);
  saveResults(matrix, rowsSum, prod);

  return 0;
}