#include "main.h" // libraries

int main(void)
{
  double matrix[10][10]; // Space for matrix 10x10

  importMatrix(matrix); // Import
  
  sortMatrix(matrix); // Sorting
  
  // Get cols below main diagonal, populate remaining with nan
  double diagonalMatrix[10][10]; // Cols below diagonal matrix
  selectF(matrix, diagonalMatrix);
  
  double max[10]; // Highest value from each diagonal col
  selectHighest(diagonalMatrix, max);
  
  double productVal = product(max); // Product of diagonal cols' max
  
  saveResults(matrix, max, productVal); // Save resultst to txt file

  return 0;
}


void importMatrix(double matrix[][10]) {
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


void swap(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}


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


void sortMatrix(double arr[][10]) {
  for (int i = 0; i < 10; i++)
    bubbleSort(arr[i], 10, 1);
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


void selectCol(double arr[][10], double col[], int n) {
  int j = 0;
  for (int i = 0; i < 10; i++)
    col[j++] = arr[i][n];
}


void selectHighest(double arr[][10], double max[]) {
  double col[10]; // Placeholder for each column

  for (int i = 0; i < 10; i++) {
    selectCol(arr, col, i); // Select a col
    extern void bubbleSort(double [], int, int);
    bubbleSort(col, 10, 1); // Sort it

    int j = 0;
    while (isnan(col[j])) j++;

    max[i] = col[j]; // Select the highest values
    if (j == 10) max[i] = NAN; // Whole column is NAN
  }
}


double product(double arr[]) {
  double p = 1; // Product
  for (int i = 0; i < 10; i++)
    if(!isnan(arr[i]))
      p *= arr[i];
  return p;
}


void saveResults(double matrix[][10], double max[], double productVal) {
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
    fprintf(save, "%s", "Under main diagonal, col min:\n");
    for (int i = 0; i < 10; i++)
      fprintf(save, "%8.1f", max[i]);

    // Product value
    fprintf(save, "%s", "\nProduct value:\n");
    fprintf(save, "%16.6e", productVal);
  }

  fclose(save);
}