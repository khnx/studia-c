/*
  * This file contains useful utility functions. They may be used
  * To display arrays in various formatted ways, or be useful from
  * Other code-maitaining purpose.
  * Another category of functions in this file are functions that
  * Keep repeating themselves in many files in this repository.
*/

#include "utils.h"


int isEven(long int n)
{
  return n % 2;
}


void createName(char *filename)
{
  // System time
  time_t timer;
  time(&timer);

  // Convert time (from timer) to string and save it to filename
  sprintf(filename, "%li", timer);
  // Add ext
  strcat(filename, ".dat");
}


void showArrayRow(double arr[], int size)
{
  int i;
  for (i = 0; i < size; i++) {
    printf("%10.3lf", arr[i]);
  }
  printf("\n");
}


void showArrayCol(double arr[], int size)
{
  int i;
  for (i = 0; i < size; i++) {
    printf("%10.3lf\n", arr[i]);
  }
  printf("\n");
}


void showMatrix(double arr[][10], int size)
{
  int i;
  for (i = 0; i < size; i++) {
    int j;
    for (j = 0; j < 10; j++)
      printf("%10.3lf", arr[i][j]);
    printf("\n");
  }
  printf("\n");
}