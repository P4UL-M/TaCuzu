#ifndef DATA
#define DATA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} INDEX;

unsigned int *createArray(int size);
<<<<<<< HEAD
void modifyValue(unsigned int *array, index index, bool value);
bool getValue(unsigned int *array, index index);
unsigned int *transpose(unsigned int *a, int n);
=======
void modifyValue(unsigned int *array, INDEX INDEX, bool value);
bool getValue(unsigned int *array, INDEX INDEX);
>>>>>>> 1e055c42f106d21709e0d9d55b742f2dcbacec08

#endif