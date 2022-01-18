/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 */

/*
  * Calculate values of given function in specified domain.
  * Save results to a file.
  * Draw a plot for the results.
*/

#include <stdio.h>
#include <math.h>


double math_function(double);


int main(void)
{
  /* Domain min/max. */
  const double domain[] = { 1.2, 3.1 };

  /* Domain step. */
  double step = (domain[1] - domain[0]) / 100;

  FILE *file = fopen("results.dat", "w");

  /* File exists. */
  if (file != NULL) {
    for (double x = domain[0]; x < domain[1]; x += step) {
      double y = math_function(x);

      /* Save results only if they exist. */
      if ( ! isnan(y))
        fprintf(file, "%10.5lf%10.5lf\n", x, y);
    }

    fclose(file);

  }
  /* File doesn't exist. */
  else {
    fprintf(stderr, "Error: File did not open correctly.\n");
    return -1;
  }

  return 0;
}


/* Carry out the mathematical function. */
double math_function(double x) {
  double log1 = log(x) / log(10);
  /* Error: Not a number. */
  if (isnan(log1))
    return NAN;
  /* Error: Zero division. */
  if (pow(log1, 2) == -3)
    return NAN;

  return 5 / (pow(log1, 2) + 3);
}