#ifndef CACHE
#define CACHE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

typedef struct
{
    long long int hash;
    SizedList *l;
    UT_hash_handle hh;
} HashEntry;

long long int hashCode(SizedList *l);
void add_entry(SizedList *l);
SizedList *find_entry(int hashCode);

#endif