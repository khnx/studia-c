/*

  * Author: Radosław Smoter
  * Name: smoter_r_wp_2.c
  * OS:
  * Ubuntu 21.10
  * To compile:
  * gcc -Wall smoter_r_wp_2.c -o smoter_r_wp_2 -lm
  * To invoke:
  * ./smoter_r_wp_2

*/

// Add libraries
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "string.h"

// Do math; print to file
// domain start, domain end, domain step
void getRecords(double, double, double);

// Count first expression
// Value
double countFirst(double);
// Count second expression
// Value
double countSecond(double);
// Count third expression
// Value
double countThird(double);

// Carry out equations
int main(void)
{
  // xp, xk - domain boundaries
  const double xp = .5; // xk - domain boundary low
  const double xk = .9; // xk - domain boundary high
  const double dx = 0.002; // Domain step

  getRecords(xp, xk, dx);

  return 0;
}

void getRecords(double xp, double xk, double dx)
{
  /* Create unique name for new file (time in sec + ext) */

  time_t timer; // System time
  char filename[32]; // File name string buffer

  // Get sys time
  time(&timer);
  // Convert time (from timer) to string and save it to filename
  sprintf(filename, "%li", timer);
  // Add ext
  strcat(filename, ".dat");

  // File pointer
  FILE *file = fopen(filename, "w");

  // Ensure file exists
  if (file != NULL)
  {
    for (double x = xp; x < xk; x += dx)
    {
      double y; // Init step result var

      if (x < .6)
        y = countFirst(x);
      else if (x >= .6 && x < .7)
        y = countSecond(x);
      else
        y = countThird(x);
      
      // Save only if number encountered
      if (y != NAN)
        fprintf(file, "%f\t%f\n", x, y);
    }
  }

  // Close file
  fclose(file);

  return;
}

/*
  * If dangerous operations are encountered, verify wether
  their values are numbers; otherwise return NAN.
*/

double countFirst(double x)
{
  double log1 = log(pow(x, 2));
  double log2 = log(pow(x, 3));
  // Check if logarithms are numbers
  if (isnan(log1) || isnan(log2)) return NAN;
  return 1.7 - log1 + 3.2 * log2 / log(10);
}

double countSecond(double x)
{
  double log1 = log(x - 1.2);
  // Check if logarithm is a number
  if (isnan(log1)) return NAN;
  double sqrt1 = pow(3 * x + log1, 1/2);
  // Check if root is a number
  if (isnan(sqrt1)) return NAN;
  return sqrt1;
}

double countThird(double x)
{
  return 2.7 + 4 * pow(x, 2) + 2.3 * pow(x, 3);
}