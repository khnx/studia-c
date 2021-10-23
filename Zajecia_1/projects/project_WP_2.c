/*

  * To compile:
  * gcc -Wall -g project_WP_2.c -o project_WP_2 -lm
  * To invoke:
  * ./project_WP_2

*/

// Add libraries
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void getRecords(double, double, char *);

int main(void)
{
  // a, b - consts
  const double a = 3.2;
  const double b = 9.3;

  // File name
  char *filename = "plik.txt";

  getRecords(a, b, filename);

  return 0;
}

void getRecords(double a, double b, char *filename)
{
  // x, y - values on X, Y axes
  // dx - velocity of change
  double x, y, dx;

  // // File constant
  FILE *file;

  // Open file in write mode
  file = fopen(filename, "w");

  // Do math
  dx = (b - a) / 100;

  for (x = a; x < b; x += dx)
  {
    y = sqrt(fabs(sin(x)));
    // Print to file
    fprintf(file, "%9.6f %9.6f\n", x, y);
  }

  // Clode file
  fclose(file);

  return;
}