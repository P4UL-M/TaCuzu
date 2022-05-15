/*TaCuzu
Paul Mairesse and Axel Loones
This file contains all operation for the generation*/
#ifndef GENERATION
#define GENERATION
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struc for matrix with their size
typedef struct
{
    unsigned int size;
    unsigned int *data;
} SizedList;

// struc for list of matrix with their number
typedef struct
{
    unsigned int size;
    SizedList **data;
} ListSizedList;

unsigned int *generate_grid(unsigned int size);                         // generate a grid with the size given
SizedList *list_lines(unsigned int size);                               // generate a list of lines with the size given
SizedList *extend(SizedList *l1, SizedList *l2);                        // extend a matrix of lines with another matrix given
ListSizedList *knapsack(int i, int target, int k, SizedList *A, int N); // find all set of k elements in A with sum of target
ListSizedList *appendList(ListSizedList *l, SizedList *e);              // append a matrix to a list of matrix
void freeList(ListSizedList *l);                                        // free a list of matrix

#endif