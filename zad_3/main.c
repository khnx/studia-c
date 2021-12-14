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
	char *filename = "results.txt";
	char *filemode = "w";
	FILE *pFile;
	pFile = fopen(filename, filemode);
	if (pFile != NULL) {
		fprintf(pFile, "THE_SUM = %.6f\n", sum);
		fclose(pFile);
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