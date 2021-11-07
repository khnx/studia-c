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

  // Get cols below main diagonal, populate rest with zeros
  double diagonalMatrix[10][10]; // Cols below diagonal matrix
  extern void selectF(double [][10], double [][10]);
  selectF(matrix, diagonalMatrix);

  // Select the highest value from each diagonal col
  double max[10];
  extern void selectHighest(double [][10], double []);
  selectHighest(diagonalMatrix, max);

  // Count product of diagonal cols' max
  extern double product(double []);
  double productVal = product(max);

  // Save resultst to txt file
  void saveResults(double [][10], double [], double );
  saveResults(matrix, max, productVal);

  return 0;
}