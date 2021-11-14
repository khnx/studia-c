#include "stdio.h"
#include "math.h"

void shellSort(double v[], int n, int mode);

int main(void)
{
  double arr[] = { 12, 123, 42, 44, 41, 13, 56 };
  int n = sizeof(arr) / sizeof(double);

  shellSort(arr, n, -1);
  
  for (int i = 0; i < n; i++)
    printf("%5.f", arr[i]);

  return 0;
}

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