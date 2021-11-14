#include "stdio.h"
#include "math.h"

/*
  * Exchange two values
  * Parameters: pointer to value1, pointer to value2
*/
void exch(double *val1, double *val2)
{
  double temp = *val1;
  *val1 = *val2;
  *val2 = temp;
}

/*
  * Sort an array of length n
  * If third parameter set to any value that evaluates as true
  * Sorts increasingly, if set to to 0, sorts in decreasing order
  * Parameters: array, array's length, sorting mode
*/
void shellSort(double v[], int n, int mode)
{
  int gap, i, j, temp;

  for (gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
    {
      if(mode)
        for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap)
          exch(&v[j], &v[j+gap]);
      else
        for (j = i-gap; j >= 0 && v[j] < v[j+gap]; j -= gap)
          exch(&v[j], &v[j+gap]);
    }
}

void straightenMatrix(double array[], double matrix[][10])
{
  int k = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      array[k++] = matrix[i][j];
}

void makeMatrix(double matrix[][10], double array[0])
{
  int k = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrix[i][j] = array[k++];
}

void sortMatrix(double matrix[][10]) {
  double array[100];
  straightenMatrix(array, matrix);
  shellSort(array, 100, 0);
  makeMatrix(matrix, array);
  }