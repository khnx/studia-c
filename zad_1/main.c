/*
  * Calculate values of given function in specified domain.
  * Save results to a file.
  * Draw a plot for the results.
*/

#include <stdio.h>
#include <math.h>


int main(void)
{
  /* Domain min */
  const double xp = 1.2;
  /* Domain max */
  const double xk = 3.1;

  char *filename = "results.dat";

  /* Domain step */
  double dx = (xk - xp) / 100;

  FILE *file = fopen(filename, "w");

  /* Ensure file exists */
  if (file != NULL)
    for (double x = xp; x < xk; x += dx) {
      double log1 = log(x) / log(10);
      /* Save if result is a real number */
      if (!isnan(log1)) {
        double y = 5. / (3. + pow(log1, 2));
        fprintf(file, "%f\t%f\n", x, y);
      }
    }

  fclose(file);

  return 0;
}