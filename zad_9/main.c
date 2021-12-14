/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*
  * Draw any plot. Read pairs of values (x, y), save them to a txt file.
  * Choose a formula for the approximation function, e.g.
  * y(x) = a_0 + a_1 * x + a_2 * x^2 + a_3 * x^3 + a_4 * x^4
  * Select 5 pairs (x, y) from the txt file.
  * Create system of linear equations for all 5 (x, y).
  * Solve the system for all a_i, which are the approximation coefficients, using Gauss-Seidel method.
*/

/*
  For 3 arguments:
  a_1 * x_1^0 + a_2 * x_1^1 + a_3 * x_1^2 = y_1
  a_1 * x_2^0 + a_2 * x_2^1 + a_3 * x_2^2 = y_2
  a_1 * x_3^0 + a_2 * x_3^1 + a_3 * x_3^2 = y_3
  Change it to:
  a_1 = 1 / x_1^0 * (y_1 - a_2 * x_1^1 - a_3 * x_1^2)
  a_2 = 1 / x_2^1 * (y_2 - a_1 * x_2^0 - a_3 * x_2^2)
  a_3 = 1 / x_3^2 * (y_3 - a_1 * x_3^0 - a_2 * x_3^1)
  count a_1 with a_2 = 0 and a_3 = 0
  repeat for m times
    count a_2  with a_1 from the previous result and with preset a_3
    count a_3 with the two previous results
    coutn a_1 with the two previus results
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* Number of elements to pull out of the file. */
#define N 10

/* loaddata did not return valid data. */
#define ERR_EMPTY_FILECONTENT -10
/* File did not open correctly. */
#define ERR_INVALID_FILE NULL
/* File name is an empty string. */
#define ERR_EMPTY_FILENAME NULL


double *load_data(char *);
double *approx_func(double);
void split_data(double *, double *, double *);
double **extract(double *[], double *);
void approx_val(double **M);


int main(int argc, char const *argv[])
{
  /* filecontent is an array with format XYXY... */
  double *filecontent = load_data("plik.txt");

  /* End the program, because it failed: loaddata did not return valid data. */
  if (filecontent == NULL) {
    fprintf(stderr, "Error: Data Did not Load Correctly.\n");
    return ERR_EMPTY_FILECONTENT;
  }

  double X[N/2];
  double Y[N/2];

  split_data(filecontent, X, Y);

  /* Free filecontent, because it's no longer used. */
  if (filecontent != NULL) free(filecontent);

  double *approx[N/2];
  for (int i = 0; i < N/2; i++)
    approx[i] = approx_func(X[i]);
  
  for (int i = 0; i < N/2; i++) {
    for (int j = 0; j < N/2; j++)
      printf("%15.7lf", *(*(approx+i)+j) );
    printf("\n");
  }

  printf("\n");
  
  double **extracteddata = extract(approx, Y);

  for (int i = 0; i < N/2; i++) {
    for (int j = 0; j < N/2; j++)
      printf("%15.7lf", *(*(extracteddata+i)+j));
    printf("\n");
  }

  approx_val(extracteddata);

  printf("\n");

  for (int i = 0; i < N/2; i++) {
    for (int j = 0; j < N/2; j++)
      printf("%15.7lf", *(*(extracteddata+i)+j));
    printf("\n");
  }

  return 0;
}


/* Function loads exactly n floating point numbers and returns them as an array. */
double *load_data(char *filename) {
  /* Filename is an Empty String. */
  if (strcmp(filename, "") == 0) {
    fprintf(stderr, "Error: File Name is an Empty String.\n");
    return ERR_EMPTY_FILENAME;
  }

  /* Memory for n Elements. */
  double *filecontent = malloc(sizeof(double) * N);

  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    /* End of the File Indicator. */
    _Bool isEOF = 1;
    /* Buffer for the File Output. */
    double *fp = malloc(sizeof(double));

    long long i;
    for (i = 0; isEOF == 1 && i < N; i++) {
      isEOF = fscanf(file, "%lf", fp);
      filecontent[i] = *fp;
    }

    /* Add a flag to end the array. */
    free(fp);
    fclose(file);
  }
  /* The File Did Not Open Correctly. */
  else {
    fprintf(stderr, "Error: The File %s Did Not Open Correctly.\n", filename);
    return ERR_INVALID_FILE;
  }

  /* Everything Handles Correctly. */
  return filecontent;
}


/* Splits one array with length n to two arrays with length n/2. With every odd element in one array and every even in the other one. */
void split_data(double *A, double *X, double *Y) {
  /* For A */
  unsigned long long i = 0;
  /* For X */
  unsigned long long k = 0;
  /* For Y */
  unsigned long long j = 0;

  while (i < N) {
    if (i % 2 == 0)
      X[k++] = A[i];
    else
      Y[j++] = A[i];
    i++;
  }
}


/* Returns an array. For x: [x^0, x^1, ..., x^(n-1)], where n is the length of the polynomial. */
double *approx_func(double x) {
  /* Approximation function */
  double *approx = malloc(sizeof(double) * N / 2);

  /* Number of approximation elements in the approximation function */
  long long i = 0;
  /* Sets the approximation function up to the powerset of n-1 (including x^0) and not over x^4. */
  while (i < N / 2) {
    approx[i] = pow(x, i);
    i++;
  }

  return approx;
}


/* Change the extended matrix (matrix with results) into a form that extracts a factor from the diagonal from each row, and sets this factor to 1, so all remaining factors from that row are divided by this factor. */
double **extract(double *matrix[], double results[]) {
  /* All factors with results, but factors on the diagonals. */
  double **A = malloc(sizeof(double) * (N/2));
  for (int i = 0; i < N/2; i++) {
    double *val = malloc(sizeof(double) * (N/2));
    *(A+i) = val;
  }

  /* Onto matrix A:
  add elements from matrix, except from the diagonal,
  multiply them by -1.0,
  add elements from results to each corresponding row,
  divide each row by corresponding factor from the diagonal. */
  for (int i = 0; i < N/2; i++) {
    /* Elements from the diagonal. */
    double factor;
    /* Current element in A. */
    int m = 0;

    for (int j = 0; j < N/2; j++) {
      if (i != j) {
        *(*(A+i)+m) = *(*(matrix+i)+j) * -1.0;
        m++;
      } else
        factor = *(*(matrix+i)+j);
    }

    /* Elements from the results. */
    *(*(A+i)+m) = *(results+i);
    m++;

    /* Divide by factor */
    for (int j = 0; j < N/2; j++)
      *(*(A+i)+j) /= factor;
  }

  return A;
}


double sum_matrix(double **M) {
  double sum = 0;
  for (int i = 0; i < N/2; i++)
    for (int j = 0; j < N/2; j++)
      sum += *(*(M+i)+j);
  return sum;
}


/* Matrix can now be represented as this equation:
  a_1 = 1 / x_1^0 * (- a_2 * x_1^1 - a_3 * x_1^2 + y_1)
  a_2 = 1 / x_2^1 * (- a_1 * x_2^0 - a_3 * x_2^2 + y_2)
  a_3 = 1 / x_3^2 * (- a_1 * x_3^0 - a_2 * x_3^1 + y_3)

 */
void approx_val(double **M) {
  /* Set a_i to 0 for the first row */
  for (int i = 0; i < N/2; i++)
    for (int j = 0; j < N/2-1; j++)
      if (j >= i)
        *(*(M+i)+j) = 0;

  printf("\n");
  for (int i = 0; i < N/2; i++) {
    for (int j = 0; j < N/2; j++)
      printf("%15.7lf", *(*(M+i)+j));
    printf("\n");
  }      
  
  /* All rows */
  for (int i = 0; i < N/2; i++) {
    double coeff = sum_matrix(M);
    /* Insert new value for coefficients */
    for (int j = 0; j < N/2; j++)
      if (i != j)
        *(*(M+j)+i) = coeff;

    printf("\n");
    for (int i = 0; i < N/2; i++) {
      for (int j = 0; j < N/2; j++)
        printf("%15.7lf", *(*(M+i)+j));
      printf("\n");
  }  
  }
}