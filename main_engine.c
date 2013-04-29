#include "main_engine.h"

int backtrack(int x, int y)
{
    int temp, i;
    if (outputArray[x][y] == 0) {
        for (i = 1; i < 10; i++) {
            temp = input_value(x, y, i);
            if (temp > 0) {
                outputArray[x][y] = temp;
                if (x == 8 && y == 8) {
                    return 1;
                } else if (x == 8) {
                    if (backtrack(0, y + 1))
                        return 1;
                } else {
                    if (backtrack(x + 1, y))
                        return 1;
                }
            }
        }
        if (i == 10) {
            if (outputArray[x][y] != array[x][y])
                outputArray[x][y] = 0;
            return 0;
        }
    } else {
        if (x == 8 && y == 8) {
            return 1;
        } else if (x == 8) {
            if (backtrack(0, y + 1))
                return 1;
        } else {
            if (backtrack(x + 1, y))
                return 1;
        }
    }
    return 0;
}


int input_value(int x, int y, int value)
{
    int i, j;
    /*check columns and rows */
    for (i = 0; i < 9; i++) {
        if (value == outputArray[i][y] || value == outputArray[x][i])
            return 0;
    }
    /*check boxes */
    if (x < 3) {
        if (y < 3) {
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else if (y < 6) {
            for (i = 0; i < 3; i++) {
                for (j = 3; j < 6; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else {
            for (i = 0; i < 3; i++) {
                for (j = 6; j < 9; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        }
    } else if (x < 6) {
        if (y < 3) {
            for (i = 3; i < 6; i++) {
                for (j = 0; j < 3; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else if (y < 6) {

            for (i = 3; i < 6; i++) {
                for (j = 3; j < 6; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else {
            for (i = 3; i < 6; i++) {
                for (j = 6; j < 9; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        }
    } else {
        if (y < 3) {
            for (i = 6; i < 9; i++) {
                for (j = 0; j < 3; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else if (y < 6) {
            for (i = 6; i < 9; i++) {
                for (j = 3; j < 6; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        } else {
            for (i = 6; i < 9; i++) {
                for (j = 6; j < 9; j++) {
                    if (value == outputArray[i][j]) {
                        return 0;
                    }
                }
            }
        }
    }
    return value;
}
