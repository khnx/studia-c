/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
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
  set coefficients to zeros
  repeat for until changes between coefficients are insignificant
    cout i-th coefficient with 
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
void split_data(double *, double *, double *);
void approximate(double A[][N/2], double B[]);


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

  double approx[N/2][N/2];
  for (int i = 0; i < N/2; i++)
    for (int j = 0; j < N/2; j++)
      approx[i][j] = pow(X[i], j);

  printf("\n");

  approximate(approx, Y);

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
  int i = 0;
  /* For X */
  int k = 0;
  /* For Y */
  int j = 0;

  while (i < N) {
    if (i % 2 == 0)
      X[k++] = A[i];
    else
      Y[j++] = A[i];
    i++;
  }
}


void printV(double v[], unsigned long long iter) {
  /* Coefficents */
  for (int i = 0; i < N/2; i++)
    printf("%11s%d", "a_", i);
  printf("\n");
  for (int i = 0; i < N/2; i++)
    printf("%12.5lf", v[i]);
  printf("\n");

  /* Number of iteration */
  printf("Current iteration number is: %llu\n", iter++);
  for (int i = 0; i < 50; i++)
    printf("%s", "-");
  printf("\n\n");
}

_Bool approx_err(double error[], double v[]) {
  for (int i = 0; i < N/2; i++)
    if (fabs(v[i] - error[i]) > 1e-1)
      return 1;
  return 0;
}


/* Find coefficients for the approximation polynomial.*/
void approximate(double X[][N/2], double Y[]) {
  /* Iteration number */
  unsigned long long iter = 1;
  /* Coefficients of the approximation equation */
  double coeff[N/2];
  /* Error between each iteration of approximation. Has exact value as coeff in the previous iteration. Initialised to ones. */
  double error[N/2];

  for (int i = 0; i < N/2; i++) {
    for (int j = 0; j < N/2; j++) {
      /* populate coeff with zeros */
      coeff[i] = 0;
      /* populate error with ones */
      error[i] = 1;
    }
  }

  /* Repeat until error is significant. */
  while (approx_err(error, coeff)) {
    /* Calculate new errors for each coeff */
    for (int i = 0; i < N/2; i++)
      error[i] = coeff[i];

    for (int i = 0; i < N/2; i++) {
      /* Sum of elements (coefficients * powerset) from each row */
      double row_sum = 0;
      for (int j = 0; j < N/2; j++)
        if (i != j)
          /* Multiply by -1.0, because it's substraction */
          row_sum += X[i][j] * coeff[j] * (-1.0);
      /* Add Y's value to row */
      row_sum += Y[i];
      /* Divide all elements from the row by X's value that stands before the calculated coefficient. */
      coeff[i] = row_sum / X[i][i];
    }

    iter++;
  }
  printV(coeff, iter);
}