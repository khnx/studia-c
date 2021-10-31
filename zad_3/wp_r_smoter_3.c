#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*
	* Author: Radosław Smoter
	* OS: Ubuntu 21.10
	* To compile: gcc -Wall filename.c -o filename -lm
	* To invoke: ./filename
*/

/* 
	* Count a sum with specified parameters
	* Parameters:
	* Domain boundaries: first min, then max,
	* domain step, function error, range begin
*/
double doSum(const double [], double, double, int);

/*
	* Count a mathematical function with specified parameters
	* Parameters:
	* Domain value, iteration number specifier
*/
double countFunc(double x, int k);

int main(void)
{
  // Sum consts
  const double error = .000016; // Function error
  const double step = .01; // Domain step
  const double domain[] = { 3., 4. }; // Domain boundaries
	const int k = 1; // Sum iterator beginning

  const double sum = doSum(domain, step, error, k);
	printf("THE_SUM = %.6f\n", sum);

  return 0;
}

double doSum(
	const double domain[], double step, double error, int k)
{

	double sum = .0; // Total sum

	for (double x = domain[0]; x < domain[1]; x += step) {

		double elem; // Partial sum; for each domain step
		int l = k; // Local copy of sum iterator

		// Iterate, while element value is significant;
		// When drops below error, stop the loop
		do
		{
			elem = countFunc(x, l);
			sum += elem;
			l++;

		} while (elem > error);

	}

	return sum;
}

double countFunc(double x, int k)
{

	// Partial value; for sinus
	double sinVal = sin(x / pow(2, k));
	// Partial value; for cosinus
	double cosVal = cos(x / pow(2, k));
	// Partial value; for fraction
	double fractVal = 1 / pow(2, k);

	return fractVal * (sinVal + cosVal);
}