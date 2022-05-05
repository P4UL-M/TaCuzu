#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include <stdbool.h>
#include <math.h>
#include "uthash.h"
#include "cache.h"

long long int hashCode(SizedList *l)
{
    long long int res = 0;
    int myprime[] = {7243, 7523, 7907};
    for (int i = 0; i < 3; i++)
    {
        res += l->data[i] * myprime[i];
    }
    return res;
}

HashEntry *mycache = NULL;

void add_entry(SizedList *l)
{
    HashEntry *s = (HashEntry *)malloc(sizeof(HashEntry));
    s->l = l;
    s->hash = hashCode(l);
    HASH_ADD_INT(mycache, hash, s);
}

SizedList *find_entry(int hashCode)
{
    HashEntry *s;

    HASH_FIND_INT(mycache, &hashCode, s);
    return s->l;
}
