#ifndef CACHE
#define CACHE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

typedef struct
{
    long long int hash;
    ListSizedList *l;
    UT_hash_handle hh;
} HashEntry;

long long int hashCode(SizedList *l);
void add_entry(long long int hash, ListSizedList *l);
ListSizedList *find_entry(int hashCode);

#endif