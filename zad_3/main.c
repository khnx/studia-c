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
#include <tgmath.h>
#include <stdlib.h>


double countFunc(double, int);


int main( void ) {
	/* Function error */
  const double error = .000016;
	/* Domain step */
  const double step = .01;
	/* Domain */
  const double domain[] = { 3., 4. };
	/* Total sum */
	double sum = .0;

	for (double x = domain[0]; x < domain[1]; x += step) {
		/* Partial sum; for each domain step */
		double elem;
		/* Sum iterator */
		size_t k = 1;
		/* Iterate, while element value is significant;
		When drops below error, stop the loop */
		do {
			elem = countFunc(x, k);
			sum += elem;
			k++;
		} while ( fabs( elem ) > error );
	}

	printf("THE_SUM = %.6f\n", sum);

	/* Save to a file */
	FILE *file = fopen("results.txt", "w");
	if (file == NULL) {
		perror( "main" );
		exit( EXIT_FAILURE );
	}
	fprintf(file, "THE_SUM = %.6f\n", sum);

  exit( EXIT_SUCCESS ); 		// Implicit fclose().
}

/* Calculate a mathematical function */
double countFunc(double x, int k) {
	/* Partial values*/
	double sinVal = sin(x / pow(2, k));
	double cosVal = cos(x / pow(2, k));
	double fractVal = 1 / pow(2, k);

	return fractVal * (sinVal + cosVal);
}