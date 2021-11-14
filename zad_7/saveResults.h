/*
  * Save results of the task to a txt file
  * Parameters: array 2D, array, product value
*/
void saveMatrixToFile(double matrix[][10], char *filename) {
  // File pointer
  FILE *file = fopen(filename, "w");

  if (file != NULL) {
    // Matrix entires
    fprintf(file, "Matrix 10x10 of random numbers with seed '%i'\n", SEED);
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++)
        fprintf(file, "%6.1lf", matrix[i][j]);
      fprintf(file, "\n");
    }
    fprintf(file, "\n");
  }

  fclose(file);
}