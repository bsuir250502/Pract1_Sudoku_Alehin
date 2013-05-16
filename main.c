#include "main_engine.h"

int main()
{
    int i, j, k = 0, *array, *outputArray;
    FILE *inFile, *outFile;
    array = (int*) calloc(PUZZLE_CELLS, sizeof(int));
    outputArray = (int*) calloc(PUZZLE_CELLS, sizeof(int));
    inFile = fopen("sudoku.in", "r+");
    outFile = fopen("sudoku.out", "w+");
        for (i = 0; i < PUZZLE_CELLS; i++)
            fscanf(inFile, "%d", &array[i]);

        for (i = 0; i < PUZZLE_CELLS; i++)
            outputArray[i] = array[i];

        if (backtrack(0, array, outputArray)) {
            for (i = 0; i < 9; i++) {
                for (j = 0; j < 9; j++)
                    fprintf(outFile, "%d ", outputArray[k++]);
                fprintf(outFile, "\n");
            }
        } else
            fprintf(outFile, "No solution\n");
    free(array);
    free(outputArray);
    fclose(inFile);
    fclose(outFile);
    return 0;
}
