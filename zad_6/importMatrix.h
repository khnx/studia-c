#include "stdio.h"

/*
  * Import matrix from "matrix.txt" file
  * Parameters: two dimensional array with fixed 2nd dim to 10
*/
void importMatrix(double matrix[][10])
{
  FILE *file = fopen("matrix.txt", "r"); // Matrix file

  double fp; // Number
  int isEOF; // Is EOF encountered
  int i = 0; // Row counter
  int j = 0; // Column counter
  do {
    isEOF = fscanf(file, "%lf", &fp);
    
    if (j >= 10) // Go to a new row
    {
      j = 0;
      i++;
    }
    if (isEOF != EOF) // Don't assign EOF
      matrix[i][j] = fp;

    j++; // Each new entry
  } while (isEOF != EOF);

  fclose(file);
}