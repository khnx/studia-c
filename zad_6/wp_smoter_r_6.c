#include "stdio.h"

#include "addOns.h" // Custom libraries

int main(void)
{

  double matrix[10][10]; // Space for matrix 10x10

  // Import
  extern void importMatrix(double [][10]);
  importMatrix(matrix);

  // Sorting
  extern void sortMatrix(double arr[][10]);
  sortMatrix(matrix);


  return 0;
}