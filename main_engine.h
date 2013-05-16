#ifndef _MYLIB_H_
#define _MYLIB_H_
#define PUZZLE_CELLS 81
#define PEER_LEN 20
#include <stdio.h>
#include <stdlib.h>

int check_value(int, int, int*, int*);
int backtrack(int, int*, int*);
#endif