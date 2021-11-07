#include "stdio.h"
#include "math.h"

void selectF(double arr[][10], double diagonal[][10]);
void populateArr(double arr[][10]);
void show(double arr[][10]);

int main(void)
{
  
  double arr[10][10];
  double diagonal[10][10];

  populateArr(arr);
  selectF(arr, diagonal);
  show(arr);
  printf("\n");
  show(diagonal);

  return 0;
}

void selectF(double arr[][10], double diagonal[][10]) {
  int m = 0; // diagonal rows
  int n = 0; // diagonal cols
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i > j) diagonal[m][n] = arr[i][j];
      else diagonal[m][n] = NAN;
      n++;
    }
    m++;
    n = 0;
  }
}

void populateArr(double arr[][10]) {
  for (int i = 0; i  < 10; i++)
    for (int j = 0; j < 10; j++)
      arr[j][i] = 1;
}

void show(double arr[][10]) {
  for (int i = 0; i  < 10; i++) {
    for (int j = 0; j < 10; j++)
      printf("%6.f", arr[i][j]);
    printf("\n");
  }
}