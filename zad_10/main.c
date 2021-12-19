/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @brief 
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Domain */
#define D_END 1.0
#define D_BEGIN 0.0

/* Constants */
#define C_1 0.0048
#define C_2 0.048
#define C_3 0.007
#define R_1 19.0
#define R_2 29.0
#define OMEGA 314.159265359

double u_1(double t) {
  return 300 * sin(OMEGA * t);
}


double f_1(double u_1, double u_c1, double u_c3) {
  return (u_1 - u_c1 - u_c3) / (R_1 * C_1);
}

double f_2(double u_1, double u_c1, double u_c3) {
  return (u_1 - u_c1 - u_c3) / (R_1 * C_1);
}

double f_3(double u_1, double u_c1, double u_c2, double u_c3) {
  return (u_1 - u_c1 - u_c3) / (R_1 * C_1) - (u_c3 - u_c2) / (R_2 * C_3);
}


int main(int argc, char const *argv[])
{
  double y_n, k_1, k_2, k_3, k_4;
  y_n = 0.0;

  double h = fabs((D_END - D_BEGIN) / 100);

  for (double t = D_BEGIN; t < D_END; t += h) {
    k_1 = h * f_1(u_1(t), t, y_n);
    k_2 = h * f_1(u_1(t), t + h / 3, y_n + k_1 / 3);
    k_3 = h * f_1(u_1(t), t + 2 * h / 3, y_n + 2 * k_2 / 3);

    y_n += (k_1 + 4 * k_2 + k_3) / 6;  
  }
  
  printf("Result: %.5e\n", y_n);

  return 0;
}


