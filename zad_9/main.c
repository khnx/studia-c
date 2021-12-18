/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @brief Approximating a function with Gauss-Seidel method
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


#include <time.h>

int main(int argc, char const *argv[])
{
  double time_spent = 0.0;
  clock_t begin_clock = clock();

  /* filecontent is an array with format XYXY... */
  double *filecontent = load_data("a.txt");

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

  approximate(approx, Y);

  clock_t end_clock = clock();
  time_spent += (double)(end_clock - begin_clock) / CLOCKS_PER_SEC;
  printf("\nThe elapsed time is %lf seconds.\n", time_spent);

  return 0;
}


/* Loads exactly n floating point numbers and returns them as an array. */
double *load_data(char *filename) {
  /* Filename is an empty string. */
  if (strcmp(filename, "") == 0) {
    fprintf(stderr, "Error: File Name is an Empty String.\n");
    return ERR_EMPTY_FILENAME;
  }

  /* Memory for n elements. */
  double *filecontent = malloc(sizeof(double) * N);

  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    /* End of the file indicator. */
    _Bool isEOF = 1;
    /* Buffer for the file output */
    double *fp = malloc(sizeof(double));

    long long i;
    for (i = 0; isEOF == 1 && i < N; i++) {
      isEOF = fscanf(file, "%lf", fp);
      filecontent[i] = *fp;
    }

    free(fp);
    fclose(file);
  }
  /* The File did not open correctly */
  else {
    fprintf(stderr, "Error: The File %s Did Not Open Correctly.\n", filename);
    return ERR_INVALID_FILE;
  }

  /* Everything went correctly */
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


/* Colors: reset, bold red, bold yellow */
#define C_RESET "\e[0m"
#define C_BRED "\e[1;31m"
#define C_BYEL "\e[1;33m"


/* Print results of the approximation (coefficients) and number of iterations. */
void printV(double v[], unsigned long long iter) {
  /* Coefficents */
  for (int i = 0; i < N/2; i++)
    printf("%11s%d", "a_", i);
  printf("\n");
  for (int i = 0; i < N/2; i++)
    printf("%s%12.5lf%s", C_BYEL, v[i], C_RESET);
  printf("\n");

  /* Number of iteration */
  printf("Current iteration number is: %s%llu%s\n",C_BRED, iter++, C_RESET);
  for (int i = 0; i < 60; i++)
    printf("%s", "-");
  printf("\n");
}


/* Calculate absolute errors between iterations of approximations of the coefficients. Ends approximation, when all of the errors drop below the level of significance. */
_Bool approx_err(double error[], double v[]) {
  /* Indicates level of significance. */
  const double MAX_ERROR = 1e-14;

  for (int i = 0; i < N/2; i++)
    if (fabs(v[i] - error[i]) > MAX_ERROR)
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

    /* Prevent iter from overflow. */
    if (iter == __INT_MAX__)
      break;
    iter++;
  }

  printV(coeff, iter);

  FILE *file = fopen("b.txt", "w");
  if (file != NULL) {
    for (int i = 0; i < N/2; i++)
      fprintf(file, "%.5lf*x^%d\n", coeff[i], i);
    fclose(file);
  }
  else {
    fprintf(stderr, "Error: File did not open successfully.\n");
    return;
  }
}