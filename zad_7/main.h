/* ***** MACROS ***** */

/* Seed for random numbers generating */
#define SEED 62


/* ***** LIBRARIES ***** */

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
  #include "../utils/utils.c" // utils for linux
#elif _WIN32
  #include "..\utils\utils.c" // utils for windows
#endif


/* ***** PROTOTYPES ***** */

/*
  * Save results of the task to a txt file
  * Parameters:
  * matrix 10x10, file name, save mode, description message
*/
void saveMatrixToFile(double [][10], char *, char *, char *);


/* Generate a matrix filled with random numbers, 2nd dim is 10 */
void randomNumbersMatrix(double [][10]);


/* Sort array v in ascending order */
void quicksort(double [], int, int);

/*
  * Co funkcja robi
  * Parametry
*/
void sortColumns(double [][10]);