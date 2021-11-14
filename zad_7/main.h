/* ***** MACROS ***** */
#define SEED 62


/* ***** INCLUDES ***** */

// Standard library headers
#include <stdio.h>
#include <stdlib.h>

// My header files
#include "../utils/utils.c"
#include "saveResults.h"


/* ***** PROTOTYPES ***** */

/* Generate a matrix filled with random numbers, 2nd dim is 10 */
void generateRandomNumbersMatrix(double matrix[][10]);
/* Sort array v in ascending order */
void quicksort(double v[], int l, int r);
void sortColumns(double matrix[][10]);
