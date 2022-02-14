/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-16

 * @copyright Copyright (c) 2021
 */

/*
  * Calculate given functions with their respectable domains.
  * Results save to a file.
  * Draw a plot for the results.
*/

#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>

/* Calculate mathematical functions */
double countFirst(double x);
double countSecond(double x);
double countThird(double x);


int main( void ) {
  /* Domain min/max*/
  const double domain[] = { 0.5, 0.9 };
  /* Domain step */
  const double step = 0.002;

  FILE *file = fopen("results.dat", "w");
  if ( file == NULL ) {
    perror( "main" );
    exit( EXIT_FAILURE );
  }
  
  for (double x = domain[0]; x < domain[1]; x += step) {
    /* Step result */
    double y;

    /* If in domain, do respectable function */
    if (x < .6)
      y = countFirst(x);
    else if (x >= .6 && x < .7)
      y = countSecond(x);
    else
      y = countThird(x);
    
    if ( ! isnan(y))
      fprintf(file, "%10.5f%10.5f\n", x, y);
    
  }

  exit( EXIT_SUCCESS );   // Implicit fclose().
}


/* If dangerous operations are encountered, verify wether their values are numbers; otherwise return NAN.*/

double countFirst(double x) {
  double log1 = log(pow(x, 2));
  double log2 = log(pow(x, 3));
  /* Verify whether numbers */
  if (isnan(log1) || isnan(log2)) return NAN;
  return 1.7 - log1 + 3.2 * log2 / log(10);
}

double countSecond(double x) {
  double log1 = log(x - 1.2);

  /* Check if not a number */
  if (isnan(log1)) return NAN;

  double sqrt1 = pow(3 * x + log1, 1/2);

  /* Check if not a number */
  if (isnan(sqrt1)) return NAN;

  return sqrt1;
}

double countThird(double x) {
  return 2.7 + 4 * pow(x, 2) + 2.3 * pow(x, 3);
}