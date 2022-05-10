#ifndef GRID
#define GRID
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int *createMask(int size, int difficulty);
void displayArray(unsigned int *a, int n);
bool checkArray(unsigned int *a, int n);
int countBits(unsigned int i);
bool checkDouble(unsigned int *a, int n);
INDEX Obtainable(unsigned int *sol, unsigned int *mask, int n);
void displayUser(unsigned int *sol, unsigned int *mask, int n);

#endif