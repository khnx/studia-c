/* ***** MACROS ***** */
#define SEED 62


/* ***** LIBRARIES ***** */

// Standard library headers
#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.c"


/* ***** PROTOTYPES ***** */

/*
  * Save results of the task to a txt file
  * Parameters: array 2D, array, product value
*/
void saveMatrixToFile(double [][10], char *, char *, char *);


/* Generate a matrix filled with random numbers, 2nd dim is 10 */
void randomNumbersMatrix(double [][10]);


/* Sort array v in ascending order */
void quicksort(double [], int, int);


void sortColumns(double [][10]);


