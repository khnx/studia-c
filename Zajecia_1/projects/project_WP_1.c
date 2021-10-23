/*

  * To compile:
  * gcc -o project_WP_1 project_WP_1.c -lm
  * To invoke:
  ./project_WP_1

*/

#include "stdio.h"
#include "math.h"

double x = .5, h;
float y, dx;
int k = 1024;

int main(void) {

  dx = 4.;
  printf("x = %i\n\n\n", k);
  
  // Sin
  y = sin(x);
  printf("x = %.1f y = sin(x) = %.9f\n", x, y);

  // Cos
  y = cos(x);
  printf("x = %f y = cos(x) = %.9f\n", x, y);

  // Tan
  y = tan(x);
  printf("x = %f y = tan(x) = %.9f\n", x, y);

  // Atan
  y = atan(x);
  printf("x = %f y = atan(x) = %.9f\n", x, y);

  // e^x
  y = exp(x);
  printf("x = %f y = exp(x) = %.9f\n", x, y);

  // Ln
  y = log(x);
  printf("x = %f y = log(x) = %.9f\n", x, y);

  // Log, base dx
  y = log(x) / log(dx);
  printf("x = %f y = log(x) / log(dx) = %.9f\n", x, y);

  // Square root
  y = sqrt(x);
  printf("x = %f y = sqrt(x) = %.9f\n", x, y);

  // Cubic root
  y = cbrt(x);
  printf("x = %f y= cbrt(x) = %.9f\n", x, y);

  return 0;
}