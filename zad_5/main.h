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
  * Swap two values
  * Parameters: value1, value2
*/
void swap(double *, double *);


/*
  * Sort an array of length n, increasingly
  * Parameters: array, array's length, monotonicity
*/
void bubbleSort(double [], int, int);


/*
  * Sort all rows of a  matrix
  * Parameters: 2D array
*/
void sortMatrix(double [][10]);


/*
  * Select entries from under the main diagonal of arr
  * Parameters: array 2D, array 2D
*/
void selectF(double [][10], double [][10]);


/*
  * Select single column from a 2D array
  * Parameters: array 2D, array, col number
*/
void selectCol(double [][10], double [], int);


/*
  * Select the highest values for each column
  * Return these values in array max
  * Parameters: array 2D, array
*/
void selectHighest(double [][10], double []);


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