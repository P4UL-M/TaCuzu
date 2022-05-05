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
void modifyValue(unsigned int *array, INDEX INDEX, bool value);
bool getValue(unsigned int *array, INDEX INDEX);
unsigned int *transpose(unsigned int *a, int n);
unsigned int sum(unsigned int *a, int n);
bool is_in(unsigned int *a, int n, unsigned int val);

#endif