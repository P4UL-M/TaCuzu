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

typedef struct
{
    unsigned int size;
    SizedList **data;
} ListSizedList;

unsigned int *generate_grid(unsigned int size);
SizedList *list_lines(unsigned int size);
SizedList *extend(SizedList *l1, SizedList *l2);
ListSizedList *knapsack(int i, int target, int k, SizedList *A, int N);
ListSizedList *appendList(ListSizedList *l, SizedList *e);
void freeList(ListSizedList *l);

#endif