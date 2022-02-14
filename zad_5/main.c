/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 */

/*
  * Read a matrix M from a file.
  * Sort elements of the matrix rows in descending order, denote as M_sort.
  * Sorting algorithm: bubble sort.
  * Select the lowest value of each column of the matrix from under the main diagonal, denote as f_j(a_ij).
  * Calculate product F of f_j(a_ij) as F(f_j(a_ij)).
  * Save the results of M_sort, f_j(a_ij), F(f_j(a_ij)) to a file.
*/

#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
#include <stdbool.h>


void importMatrix(double [][10]);
void sortMatrix(double [][10]);
void selectF(double [][10], double [][10]);
void selectLowest(double [][10], double []);
double product(double []);
void saveResults(double [][10], double [], double);


int main( void ) {
  /* Space for matrix 10x10 */
  double matrix[10][10];

  importMatrix(matrix);
  sortMatrix(matrix);
  
  /* Get cols below main diagonal, populate remaining with nan */
  /* Cols below diagonal matrix */
  double diagonalMatrix[10][10];
  selectF(matrix, diagonalMatrix);
  
  /* Lowest value from each diagonal col */
  double min[10];
  selectLowest(diagonalMatrix, min);
  
  /* Product of diagonal cols' min */
  double productVal = product(min);
  
  /* Save resultst to txt file */
  saveResults(matrix, min, productVal);

  return 0;
}


/* Import matrix from "matrix.txt" file */
void importMatrix(double matrix[][10]) {
  FILE *file = fopen("matrix.txt", "r");

  if ( file == NULL ) {
    perror( "File does not exist. ");
    exit( EXIT_FAILURE );
  }

  /* Single number from the file */
  double fp;
  /* Is EOF encountered */
  int isEOF;
  /* Row counter */
  int i = 0;
  /* Column counter */
  int j = 0;

  do {
    isEOF = fscanf(file, "%lf", &fp);
    
    /* Go to a new row */
    if (j >= 10)
    {
      j = 0;
      i++;
    }
    /* Don't assign EOF */
    if (isEOF != EOF)
      matrix[i][j] = fp;

    /* Each new entry */
    j++;
  } while (isEOF != EOF && (i*10 + j) < 100);

  fclose(file);
}


/* Exchange values of two variables */
void exch(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}


/* Sort an array. */
void bubbleSort( double arr[], int n, bool (*mode)( double a, double b ) ) {

  size_t swapCounter = 1;
  while ( swapCounter ) {
    swapCounter = 0;

    for (size_t i = 0; i < n-1; i++)
      if ( (*mode)( arr[ i ], arr[ i+1 ] ) ) {
        exch( &arr[ i ], &arr[ i+1 ] );
        swapCounter++;
      }
  }
}


bool desc( double a, double b ) {
  return ( a < b ) ? true : false;
}


/* Sort all rows of a  matrix */
void sortMatrix(double arr[][10]) {
  for (int i = 0; i < 10; i++)
    bubbleSort( arr[i], 10, desc );
}



/* Select entries from under the main diagonal of the matrix */
void selectF(double arr[][10], double diagonal[][10]) {
  /* Diagonal rows */
  int m = 0;
  /* Diagonal columns */
  int n = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i > j) diagonal[m][n] = arr[i][j];
      /* Populate with nans to avoid trash values */
      else diagonal[m][n] = NAN;
      n++;
    }
    m++;
    n = 0;
  }
}


/* Select a column from a matrix */
void selectCol(double arr[][10], double col[], int n) {
  int j = 0;
  for (int i = 0; i < 10; i++)
    col[j++] = arr[i][n];
}


bool asc( double a, double b ) {
  return ( a > b ) ? true : false;
}


/* Select the lowest values in the array arr, return them in the array max */
void selectLowest(double arr[][10], double min[]) {
  /* Placeholder for each column */
  double col[10];

  for (int i = 0; i < 10; i++) {
    selectCol(arr, col, i);
    bubbleSort(col, 10, asc);

    int j = 0;
    while (isnan(col[j])) j++;

    /* Select the highest values */
    min[i] = col[j];
    /* Whole column is NANs; no real values in a column */
    if (j == 10) min[i] = NAN;
  }
}


/* Return product of the given array */
double product(double arr[]) {
  /* Product */
  double p = 1;
  for (int i = 0; i < 10; i++)
    /* Ensure none of the entries are NAN */
    if(!isnan(arr[i]))
      p *= arr[i];
  return p;
}


/* Save results of the task to a txt file */
void saveResults(double matrix[][10], double max[], double productVal) {
  char *filename = "results.txt";
  FILE *file = fopen(filename, "w");

  if (file == NULL) {
    perror( "saveResults" );
    exit( EXIT_FAILURE );
  }

  /* Sorted matrix entires */
  fprintf(file, "%s", "Sorted matrix:\n");
  for (int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++)
      fprintf(file, "%8.1f", matrix[i][j]);
    fprintf(file, "%c", '\n');
  }

  /* Entries from under main diagonal, highest values */
  fprintf(file, "%s", "Under main diagonal, col min:\n");
  for (int i = 0; i < 10; i++)
    fprintf(file, "%8.1f", max[i]);

  /* Product value */
  fprintf(file, "%s", "\nProduct value:\n");
  fprintf(file, "%16.6e", productVal);

  fclose(file);
}