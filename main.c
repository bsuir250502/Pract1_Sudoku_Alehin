#include "main_engine.h"

int main()
{
    int i, j;
    FILE *inFile, *outFile;
    inFile = fopen("sudoku.in", "r+");
    outFile = fopen("sudoku.out", "w+");
        fprintf(outFile, "Original outputArray\n");
        for (i = 0; i < 9; i++) {
            fscanf(inFile, "%d %d %d %d %d %d %d %d %d",
                   &array[i][0], &array[i][1], &array[i][2],
                   &array[i][3], &array[i][4], &array[i][5],
                   &array[i][6], &array[i][7], &array[i][8]);
        }

        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                outputArray[i][j] = array[i][j];
            }
        }

        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                fprintf(outFile, "%d ", array[i][j]);
            }
            fprintf(outFile, "\n");
        }
        if (backtrack(0, 0)) {
            fprintf(outFile, "Solution is :");
            for (i = 0; i < 9; i++) {
                fprintf(outFile, "\n");
                for (j = 0; j < 9; j++) {
                    fprintf(outFile, "%d ", outputArray[i][j]);
                }
            }
        } else
            fprintf(outFile, "No solution\n");
    fclose(inFile);
    fclose(outFile);
    return 0;
}
