/*TaCuzu
Paul Mairesse and Axel Loones
This file contains function to interact with the cache*/
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

long long int hashCode(SizedList *l);                 // genreate a hash code for a entry
void add_entry(long long int hash, ListSizedList *l); // add an entry to the cache
ListSizedList *find_entry(int hashCode);              // find an entry in the cache

#endif