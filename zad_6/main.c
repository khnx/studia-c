#include "main.h"

int main(void)
{

  double matrix[10][10]; // Space for matrix 10x10

  importMatrix(matrix);

  sortMatrix(matrix);

  double diagonal[10][10];
  selectF(matrix, diagonal);

  double rowsSum[10];
  sumRows(diagonal, rowsSum);

  double prod = product(rowsSum);

  saveResults(matrix, rowsSum, prod);

  return 0;
}


void importMatrix(double matrix[][10])
{
  FILE *file = fopen("matrix.txt", "r"); // Matrix file

  double fp; // Number
  int isEOF; // Is EOF encountered
  int i = 0; // Row counter
  int j = 0; // Column counter
  do {
    isEOF = fscanf(file, "%lf", &fp);
    
    if (j >= 10) // Go to a new row
    {
      j = 0;
      i++;
    }
    if (isEOF != EOF) // Don't assign EOF
      matrix[i][j] = fp;

    j++; // Each new entry
  } while (isEOF != EOF);

  fclose(file);
}


void exch(double *val1, double *val2) {
  double temp = *val1;
  *val1 = *val2;
  *val2 = temp;
}


void shellSort(double v[], int n, int mode) {
  int gap, i, j;

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


void selectF(double arr[][10], double diagonal[][10]) {
  int m = 0; // diagonal rows
  int n = 0; // diagonal cols
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i > j) diagonal[m][n] = arr[i][j];
      // Populate with nans (avoid trash values)
      else diagonal[m][n] = NAN;
      n++;
    }
    m++;
    n = 0;
  }
}


void sumRows(double arr[][10], double sums[]) {
  for (int i = 0; i < 10; i++) {
    double sum = 0;
    int j;
    for (j = 0; !isnan(arr[i][j]); j++) sum += arr[i][j];
    if (j > 0) sums[i] = sum;
    else sums[i] = NAN;
  }
}


double product(double arr[]) {
  double p = 1; // Product
  for (int i = 0; i < 10; i++)
    if(!isnan(arr[i]))
      p *= arr[i];
  return p;
}


void saveResults(double matrix[][10], double array[], double product) {
  // File name string buffer
  char filename[32];
  createName(filename);
  // File pointer
  FILE *save = fopen(filename, "w");

  if (save != NULL) {
    // Sorted matrix entires
    fprintf(save, "%s", "Sorted matrix:\n");
    for (int i = 0; i < 10; i++) {
      for(int j = 0; j < 10; j++)
        fprintf(save, "%8.1f", matrix[i][j]);
      fprintf(save, "%c", '\n');
    }

    // Entries from under main diagonal, highest values
    fprintf(save, "%s", "Under main diagonal, rows sums:\n");
    for (int i = 0; i < 10; i++)
      fprintf(save, "%8.1f", array[i]);

    // Product value
    fprintf(save, "%s", "\nProduct value:\n");
    fprintf(save, "%16.6e", product);
  }

  fclose(save);
}