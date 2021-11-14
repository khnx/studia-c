/* ***** LIBRARIES ***** */
#include <stdio.h>
#include <time.h>
#include <string.h>

/* ***** PROTOTYPES ***** */

/* Check if number is even */
int isEven(long int);

/*
  * Create unique name for a file (time in sec + ext)
  * Parameters: pointer to char for file name buffer  
*/
void createName(char *);

/*
  * Display an array in formated way, as in row
  * Parameters: array, size of an array
*/
void showArrayRow(double [], int);

/*
  * Display an array in formated way, as in colummn
  * Parameters: array, size of an array
*/
void showArrayCol(double [], int);

/*
  * Display an array in formated way, as a matrix
  * Parameters: array, size of an array
*/
void showMatrix(double [][10], int);