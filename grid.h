#ifndef GRID
#define GRID
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int *createMask(int size, int difficulty);
void displayArray(unsigned int *a, int n);
bool checkArray(unsigned int *a, int n);
bool checkValid(unsigned int *a, unsigned int *mask, int n);
int countBits(unsigned int i);
bool checkDouble(unsigned int *a, int n);
INDEX *Obtainable2D(unsigned int *sol, unsigned int *mask, int n, bool debug);
INDEX *Hypothesis(unsigned int *sol, unsigned int *mask, int n, INDEX index, bool debug);
void displayUser(unsigned int *sol, unsigned int *mask, int n);
bool solvable(unsigned int *sol, unsigned int *mask, int n);

#endif