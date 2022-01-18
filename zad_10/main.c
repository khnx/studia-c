/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @brief Calculate system of derivatives with Runge-Kutta methods
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 */


#include <stdio.h>
#include <math.h>

/* Constants */
const double C1 = 0.0048;
const double C2 = 0.048;
const double C3 = 0.007;
const double R1 = 19.0;
const double R2 = 29.0;
const double OMEGA = 314.1592265359;

double U1(double t) {
  return 300 * sin(t * OMEGA);
}

double d1(double t, double U_c1, double U_c3) {
  return (U1(t) - U_c1 - U_c3) / (R1 * C1);
}

double d2(double t, double U_c2, double U_c3) {
  return (U_c3 - U_c2) / (R2 * C2);
}

double d3(double t, double U_c1, double U_c2, double U_c3) {
  return (U1(t) - U_c1 - U_c3) / (R1 * C3) - (U_c3 - U_c2) / (R2 * C2);
}

int main(void)
{
  double k1_d1, k1_d2, k1_d3;
  double k2_d1, k2_d2, k2_d3;
  double k3_d1, k3_d2, k3_d3;
  /* Initial conditions */
  double y_d1 = 0, y_d2 = 0, y_d3 = 0;
  double t = 0;

  /* Step size */
  const double h = 10e-5;

  FILE *f_d1 = fopen("d1.dat", "w");
  FILE *f_d2 = fopen("d2.dat", "w");
  FILE *f_d3 = fopen("d3.dat", "w");
  if (f_d1 == NULL || f_d2 == NULL || f_d3 == NULL) return -1;

  for (double i = 0; i < 1; i += h) {
    t += h;

    k1_d1 = h * d1(t, y_d1, y_d3);
    k1_d2 = h * d2(t, y_d2, y_d3);
    k1_d3 = h * d3(t, y_d1, y_d2, y_d3);

    k2_d1 = h * d1(t + h/3, y_d1 + k1_d1 / 3, y_d3 + k1_d3 / 3);
    k2_d2 = h * d2(t + h/3, y_d2 + k1_d2 / 3, y_d3 + k1_d3 / 3);
    k2_d3 = h * d3(t + h/3, y_d1 + k1_d1 / 3, y_d2 + k1_d2 / 3, y_d3 + k1_d3 / 3);

    k3_d1 = h * d1(t + 2/3*h, y_d1 + 2/3*k2_d1, y_d3 + 2/3*k2_d3);
    k3_d2 = h * d2(t + 2/3*h, y_d2 + 2/3*k2_d3, y_d3 + 2/3*k2_d3);
    k3_d3 = h * d3(t + 2/3*h, y_d1 + 2/3*k2_d1, y_d2 + 2/3*k2_d2, y_d3 + 2/3*k2_d3);
  
    y_d1 += (k1_d1 + 3 * k3_d1) / 4;
    y_d2 += (k1_d2 + 3 * k3_d2) / 4;
    y_d3 += (k1_d3 + 3 * k3_d3) / 4;

    fprintf(f_d1, "%16.8lf\n", y_d1);
    fprintf(f_d2, "%16.8lf\n", y_d2);
    fprintf(f_d3, "%16.8lf\n", y_d3);
  }

  fclose(f_d1);
  fclose(f_d2);
  fclose(f_d3);

  return 0;
}