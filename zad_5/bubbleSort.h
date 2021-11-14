#include <stdio.h>
#include <math.h>

/*
  * Swap two values
  * Parameters: value1, value2
*/
void swap(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}

/*
  * Sort an array of length n, increasingly
  * Parameters: array, array's length, monotonicity
*/
void bubbleSort(double arr[], int n, int monotonicity) {
  int swapCounter = 1; //

  // Do until no more swaps have been encountered
  while(swapCounter) {
    swapCounter = 0;

    for (int i = 0; i < n-1; i++)
    {
      if (monotonicity) { // Increasing
        if (arr[i] < arr[i + 1]) {
          swap(&arr[i], &arr[i + 1]);
          swapCounter++;
        }
      } else { // Decreasing
        if (arr[i] > arr[i + 1]) {
          swap(&arr[i], &arr[i + 1]);
          swapCounter++;
        }
      }
    }
  }
}

/*
  * Sort all rows of a  matrix
  * Parameters: 2D array
*/
void sortMatrix(double arr[][10]) {
  for (int i = 0; i < 10; i++)
    bubbleSort(arr[i], 10, 1);
}