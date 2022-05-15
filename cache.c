/*TaCuzu
Paul Mairesse and Axel Loones
This file contains function to interact with the cache*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include <stdbool.h>
#include <math.h>
#include "uthash.h" // librairy for hash table
#include "cache.h"

long long int hashCode(SizedList *l)
{
    // genreate a hash code for a entry
    long long int res = 0;
    int myprime[] = {7243, 7523, 7907}; // prime number
    for (int i = 0; i < 3; i++)
    {
        res += l->data[i] * myprime[i]; // add the value of the matrix to the hash, since prime number are bigger than most of the value, there is no double hash possible
    }
    return res; // return the hash code
}

HashEntry *mycache = NULL;

void add_entry(long long int hash, ListSizedList *l)
{
    // add an entry to the cache
    HashEntry *s = (HashEntry *)malloc(sizeof(HashEntry));
    s->l = l;
    s->hash = hash;
    HASH_ADD_INT(mycache, hash, s); // add the entry to the cache with uthash
}

ListSizedList *find_entry(int hashCode)
{
    // find an entry in the cache
    HashEntry *s;
    HASH_FIND_INT(mycache, &hashCode, s); // find the entry in the cache with uthash
    if (s != NULL)
    {
        return s->l;
    }
    return NULL;
}
