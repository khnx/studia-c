#include "main.h"

// Carry out equations
int main(void)
{
  double xp = 1.2; // xp - domain boundary low
  double xk = 3.1; // xk - domain boundary high

  getRecords(xp, xk);

  return 0;
}

void getRecords(double xp, double xk)
{
  const double a = 5.; // Equation const
  const double b = 3.; // Equation const

  char filename[32]; // File name
  createName(filename);

  double dx = (xk - xp) / 100; // Domain step
  FILE *file = fopen(filename, "w"); // File pointer

  if (file != NULL) // Ensure file exists
    for (double x = xp; x < xk; x += dx) { // Step
      double log1 = log(x) / log(10); // Step result
      if (!isnan(log1)) {
        double y = a / (b + pow(log1, 2));
        fprintf(file, "%f\t%f\n", x, y);
      }
    }

  fclose(file); // Close file

  return;
}