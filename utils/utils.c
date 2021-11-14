#include <stdio.h>

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