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
  * Sort elements of the matrix in descending order, denote as M_sort.
  * Sorting algorithm: shell sort.
  * Calculate sums of each row from under the main diagonal, denote as f_j(m_ij).
  * Calculate product F of f_j(m_ij) as F(f_j(m_ij)).
  * Save the results of M_sort, f_j(m_ij), F(f_j(m_ij)) to a file.
*/

#include <stdio.h>
#include <math.h>

void importMatrix(double [][10]);
void sortMatrix(double [][10]);
void selectF(double [][10], double [][10]);
void sumRows(double [][10], double []);
double product(double []);
void saveResults(double [][10], double [], double);


int main(void)
{
  /* Matrix 10x10 */
  double matrix[10][10];

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


/* Import matrix from "matrix.txt" file */
void importMatrix(double matrix[][10]) {
  char *filename = "matrix.txt";
  char *filemode = "r";
  FILE *file = fopen(filename, filemode);

  if (file != NULL) {
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
    } while (isEOF != EOF && (i*10+j) < 100);

    fclose(file);
  }
  else {
    fprintf(stderr, "Error: File did not open successfully.\n");
    return;
  }
}


/* Exchange values of two variables */
void exch(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}

/* Sort an array according to mode, ascending order  - 1, descending - 0 */
void shellSort(double v[], int n, int mode) {
  int gap, i, j;

  for (gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
    {
      if(mode)
        /* Compare elements that are gap apart from each other */
        for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap)
          exch(&v[j], &v[j+gap]);
      else
        for (j = i-gap; j >= 0 && v[j] < v[j+gap]; j -= gap)
          exch(&v[j], &v[j+gap]);
    }
}


/* Convert array 10x10 to array 100 */
void straightenMatrix(double array[], double matrix[][10]) {
  /* Index of array */
  int k = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      array[k++] = matrix[i][j];
}


/* Convert array 100 to matrix 10x10 */
void makeMatrix(double matrix[][10], double array[]) {
  int k = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrix[i][j] = array[k++];
}


/* Sort elements of the matrix in descending order */
void sortMatrix(double matrix[][10]) {
  double array[100];
  straightenMatrix(array, matrix);
  shellSort(array, 100, 0);
  makeMatrix(matrix, array);
}


/* Select entries from under the main diagonal of arr */
void selectF(double arr[][10], double diagonal[][10]) {
  /* Diagonal rows */
  int m = 0;
  /* Diagonal columns */
  int n = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i > j) diagonal[m][n] = arr[i][j];
      /* Populate with NANs to avoid trash values */
      else diagonal[m][n] = NAN;
      n++;
    }
    m++;
    n = 0;
  }
}


/* Sum elements of rows from under the main diagonal */
void sumRows(double arr[][10], double sums[]) {
  for (int i = 0; i < 10; i++) {
    double sum = 0;
    int j;
    for (j = 0; !isnan(arr[i][j]); j++) sum += arr[i][j];
    /* Don't include NANs */
    if (j > 0) sums[i] = sum;
    /* Row contains only NANs */
    else sums[i] = NAN;
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
void saveResults(double matrix[][10], double array[], double product) {
  char *filename = "results.txt";
  char *filemode = "w";
  FILE *file = fopen(filename, filemode);

  if (file != NULL) {
    /* Sorted matrix entires */
    fprintf(file, "%s", "Sorted matrix:\n");
    for (int i = 0; i < 10; i++) {
      for(int j = 0; j < 10; j++)
        fprintf(file, "%8.1f", matrix[i][j]);
      fprintf(file, "%c", '\n');
    }

    /* Entries from under main diagonal, highest values */
    fprintf(file, "%s", "Under main diagonal, rows sums:\n");
    for (int i = 0; i < 10; i++)
      fprintf(file, "%8.1f", array[i]);

    /* Product value */
    fprintf(file, "%s", "\nProduct value:\n");
    fprintf(file, "%16.6e", product);
  
    fclose(file);
  } 
  else {
    fprintf(stderr, "Error: File did not open correctly.\n");
    return;
  }

}