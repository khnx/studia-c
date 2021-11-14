#include "main.h"

int main(void)
{
  double error = .000016; // Function error
  double step = .01; // Domain step
  double domain[] = { 3., 4. }; // Domain boundaries
	int k = 1; // Sum iterator

  double sum = doSum(domain, step, error, k);
	printf("THE_SUM = %.6f\n", sum);

  return 0;
}

double countFunc(double x, int k)
{
	// Partial values
	double sinVal = sin(x / pow(2, k));
	double cosVal = cos(x / pow(2, k));
	double fractVal = 1 / pow(2, k);

	return fractVal * (sinVal + cosVal);
}

double doSum(double domain[], double step, double error, int k)
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