#ifndef DATA
#define DATA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} index;

unsigned int *createArray(int size);
void modifyValue(unsigned int *array, index index, bool value);
bool getValue(unsigned int *array, index index);
unsigned int *createMask(int size, int difficulty);

#endif