/*
  * Read a matrix M from a file.
  * Sort elements of the matrix rows in descending order, denote as M_sort.
  * Sorting algorithm: bubble sort.
  * Select the highest value of each column of the matrix from under the main diagonal, denote as f_j(a_ij).
  * Calculate product F of f_j(a_ij) as F(f_j(a_ij)).
  * Save the results of M_sort, f_j(a_ij), F(f_j(a_ij)) to a file.
*/

#include <stdio.h>
#include <math.h>


void importMatrix(double [][10]);
void sortMatrix(double [][10]);
void selectF(double [][10], double [][10]);
void selectHighest(double [][10], double []);
double product(double []);
void saveResults(double [][10], double [], double);


int main(void)
{
  /* Space for matrix 10x10 */
  double matrix[10][10];

  importMatrix(matrix);  
  sortMatrix(matrix);
  
  /* Get cols below main diagonal, populate remaining with nan */
  /* Cols below diagonal matrix */
  double diagonalMatrix[10][10];
  selectF(matrix, diagonalMatrix);
  
  /* Highest value from each diagonal col */
  double max[10];
  selectHighest(diagonalMatrix, max);
  
  /* Product of diagonal cols' max */
  double productVal = product(max);
  
  /* Save resultst to txt file */
  saveResults(matrix, max, productVal);

  return 0;
}


/* Import matrix from "matrix.txt" file */
void importMatrix(double matrix[][10]) {
  char *filename = "matrix.txt";
  char *filemode = "r";
  FILE *file = fopen(filename, filemode);

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
  } while (isEOF != EOF);

  fclose(file);
}


/* Exchange values of two variables */
void exch(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}


/* Sort an array according to monotonicity, ascending order  - 1, descending - 0 */
void bubbleSort(double arr[], int n, int monotonicity) {
  int swapCounter = 1;

  /* Do until no more swaps have been encountered */
  while(swapCounter) {
    swapCounter = 0;

    for (int i = 0; i < n-1; i++)
    {
      /* Ascending order */
      if (monotonicity) {
        if (arr[i] < arr[i + 1]) {
          exch(&arr[i], &arr[i + 1]);
          swapCounter++;
        }
        /* Descending order */
      } else {
        if (arr[i] > arr[i + 1]) {
          exch(&arr[i], &arr[i + 1]);
          swapCounter++;
        }
      }
    }
  }
}


/* Sort all rows of a  matrix */
void sortMatrix(double arr[][10]) {
  for (int i = 0; i < 10; i++)
    bubbleSort(arr[i], 10, 1);
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


/* Select the highest values in the array arr, return them in the array max */
void selectHighest(double arr[][10], double max[]) {
  /* Placeholder for each column */
  double col[10];

  for (int i = 0; i < 10; i++) {
    selectCol(arr, col, i);
    bubbleSort(col, 10, 1);

    int j = 0;
    while (isnan(col[j])) j++;

    /* Select the highest values */
    max[i] = col[j];
    /* Whole column is NANs; no real values in a column */
    if (j == 10) max[i] = NAN;
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

  if (file != NULL) {
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
  }

  fclose(file);
}