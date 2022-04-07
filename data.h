#ifndef DATA
#define DATA
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} index;

int *createArray(int size);
void modifyValue(int *array, index index, bool value);
bool getValue(int *array, index index);

#endif