/**
 * @file main.c
 * @author Radoslaw Smoter (radoslaw.smoter@student.pk.edu.pl)
 * @version 0.1
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 */

/*
	* Calculate given function.
	* Results save to a file.
	* Draw a plot for the results.
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
	/* Function error */
  double error = .000016;
	/* Domain step */
  double step = .01;
	/* Domain */
  double domain[] = { 3., 4. };
	/* Sum iterator */
	int k = 1;
	/* Total sum */
	double sum = .0;

	for (double x = domain[0]; x < domain[1]; x += step) {
		/* Partial sum; for each domain step */
		double elem;
		/* Local copy of sum iterator */
		int l = k;
		/* Iterate, while element value is significant;
		When drops below error, stop the loop */
		do {
			double countFunc(double, int);
			elem = countFunc(x, l);
			sum += elem;
			l++;
		} while (elem > error);
	}

	printf("THE_SUM = %.6f\n", sum);

	/* Save to a file */
	FILE *file = fopen("results.txt", "w");
	if (file != NULL) {
		fprintf(file, "THE_SUM = %.6f\n", sum);
		fclose(file);
	}
	/* File did not open correctly. */
	else {
		fprintf(stderr, "Error: File did not open correctly.\n");
		return -1;
	}

  return 0;
}

/* Calculate a mathematical function */
double countFunc(double x, int k) {
	/* Partial values*/
	double sinVal = sin(x / pow(2, k));
	double cosVal = cos(x / pow(2, k));
	double fractVal = 1 / pow(2, k);

	return fractVal * (sinVal + cosVal);
}