#ifndef GENERATION
#define GENERATION
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    unsigned int size;
    unsigned int *data;
} SizedList;

unsigned int *generate_grid(unsigned int size);
SizedList *list_lines(unsigned int size);

#endif