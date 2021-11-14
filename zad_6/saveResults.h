#include <stdio.h>
#include <time.h>
#include <string.h>

/*
  * Create unique name for new file (time in sec + ext)
  * Parameters: array
*/
void createName(char filename[]) {
  // System time
  time_t timer;
  time(&timer);

  // Convert time (from timer) to string and save it to filename
  sprintf(filename, "%li", timer);
  // Add ext
  strcat(filename, ".txt");
}

/*
  * Save results of the task to a txt file
  * Parameters: array 2D, array, product value
*/
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