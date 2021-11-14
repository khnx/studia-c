/* ***** LIBRARIES ***** */

#include <stdio.h>
#include <math.h>

#include "../utils/utils.c"



/* ***** PROTOTYPES ***** */

/*
  * Import matrix from "matrix.txt" file
  * Parameters: two dimensional array with fixed 2nd dim to 10
*/
void importMatrix(double [][10]);


/*
  * Exchange two values
  * Parameters: pointer to value1, pointer to value2
*/
void exch(double *, double *);


/*
  * Sort an array of length n
  * If third parameter set to any value that evaluates as true
  * Sorts increasingly, if set to to 0, sorts in decreasing order
  * Parameters: array, array's length, sorting mode
*/
void shellSort(double [], int, int);


void straightenMatrix(double [], double [][10]);


void makeMatrix(double [][10], double [0]);


void sortMatrix(double [][10]);


/*
  * Select entries from under the main diagonal of arr
  * Parameters: array 2D, array 2D
*/
void selectF(double [][10], double [][10]);


void sumRows(double [][10], double []);


/*
  * Return product value of an array
  * Parameters: array
*/
double product(double []);


/*
  * Save results of the task to a txt file
  * Parameters: array 2D, array, product value
*/
void saveResults(double [][10], double [], double);