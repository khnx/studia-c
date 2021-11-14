#include "main.h"

int main(void)
{
  double xp = .5; // xk - domain boundary low
  double xk = .9; // xk - domain boundary high
  double dx = 0.002; // Domain step

  getRecords(xp, xk, dx);

  return 0;
}

void getRecords(double xp, double xk, double dx) {
  char filename[32]; // File name string buffer
  createName(filename);
  FILE *file = fopen(filename, "w"); // File pointer
  
  if (file != NULL) // Ensure file exists
    for (double x = xp; x < xk; x += dx)
    {
      double y; // Step result

      if (x < .6) y = countFirst(x);
      else if (x >= .6 && x < .7) y = countSecond(x);
      else y = countThird(x);
      
      fprintf(file, "%f\t%f\n", x, y);
    }
  fclose(file); // Close file
}

/* If dangerous operations are encountered, verify wether their values are numbers; otherwise return NAN.*/

double countFirst(double x) {
  double log1 = log(pow(x, 2));
  double log2 = log(pow(x, 3));
  // Verify, whether numbers
  if (isnan(log1) || isnan(log2)) return NAN;
  return 1.7 - log1 + 3.2 * log2 / log(10);
}

double countSecond(double x) {
  double log1 = log(x - 1.2);
  if (isnan(log1)) return NAN; // Check whether not a number
  double sqrt1 = pow(3 * x + log1, 1/2);
  if (isnan(sqrt1)) return NAN; // Check whether not a number
  return sqrt1;
}

double countThird(double x) {
  return 2.7 + 4 * pow(x, 2) + 2.3 * pow(x, 3);
}