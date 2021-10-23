#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/* 
	* Count a sum with specified parameters
	* Domain boundaries: first min, then max,
	* domain step, function error, range begin
*/
double doSum(const double [], double, double, int);

/*
	* Count a mathematical function with specified parameters
	* Domain value, iteration number specifier
*/
double countFunc(double x, int k);

int main(void)
{
  // Sum consts
  const double error = .000016; // Function error
  const double step = .01; // Domain step
  const double domain[] = { 3., 4. }; // Domain boundaries

  double sum = doSum(domain, step, error, 1);
	printf("THE_SUM = %.6f\n", sum);

  return 0;
}

double doSum(
	const double domain[], double step, double error, int k)
{

	double sum = .0;

	for (double x = domain[0]; x < domain[1]; x += step) {

		double elem;
		int l = k;

		do
		{
			elem = countFunc(x, l);
			sum += elem;
			printf("elem%12.6f\tk%12.6f\n", elem, sum);
			l++;

		} while (elem > error);

	}

	return sum;
}

double countFunc(double x, int k)
{

	double sinVal = sin(x / pow(2, k));
	double cosVal = cos(x / pow(2, k));
	double fractVal = 1 / pow(2, k);

	return fractVal * (sinVal + cosVal);
}