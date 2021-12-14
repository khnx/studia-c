/*
  * Calculate given functions with their respectable domains.
  * Results save to a file.
  * Draw a plot for the results.
*/

#include <stdio.h>
#include <math.h>

/* Calculate mathematical function */
double countFirst(double x);
/* Calculate mathematical function */
double countSecond(double x);
/* Calculate mathematical function */
double countThird(double x);


int main(void)
{
  /* Domain min */
  double xp = .5;
  /* Domain max */
  double xk = .9;
  /* Domain step */
  double dx = 0.002;

  char *filename = "results.dat";

  FILE *file = fopen(filename, "w");
  
  /* Ensure file exists */
  if (file != NULL)
    for (double x = xp; x < xk; x += dx) {
      /* Step result */
      double y;

      /* If in domain, do respectable function */
      if (x < .6)  y = countFirst(x);
      else if (x >= .6 && x < .7) y = countSecond(x);
      else y = countThird(x);
      
      fprintf(file, "%f\t%f\n", x, y);
    }

  fclose(file); // Close file

  return 0;
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