/*

  * Author: Radosław Smoter
  * Name: Wstep do programowania - projekt 1
  * OS:
  * Ubuntu 21.10
  * To compile:
  * gcc -Wall filename.c -o filename -lm
  * To invoke:
  * ./filename

*/

// Add libraries
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "string.h"

// Do math; print to file
// domain start, domain end
void getRecords(double, double);

// Carry out equations
int main(void)
{
  const double xp = 1.2; // xp - domain boundary low
  const double xk = 3.1; // xk - domain boundary high

  getRecords(xp, xk);

  return 0;
}

void getRecords(double xp, double xk)
{
  const double a = 5.; // Equation const
  const double b = 3.; // Equation const

  /* Create unique name for new file (time in sec + ext) */

  // System time
  time_t timer;
  time(&timer);

  // File name string buffer
  char filename[32];
  // Convert time (from timer) to string and save it to filename
  sprintf(filename, "%li", timer);
  // Add ext
  strcat(filename, ".dat");

  // Domain step
  double dx = (xk - xp) / 100;

  // File pointer
  FILE *file = fopen(filename, "w");

  // Ensure file exists
  if (file != NULL)
  {
    for (double x = xp; x < xk; x += dx) // Step
    {
      // Step result
      double log1 = log(x) / log(10);
      if (!isnan(log1))
      {
        double y = a / (b + pow(log1, 2));

        fprintf(file, "%f\t%f\n", x, y);
      }
    }
  }

  fclose(file); // Close file

  return;
}