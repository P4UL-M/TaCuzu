#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>

unsigned int *createArray(int n)
{
    unsigned int *a = (unsigned int *)malloc(n * sizeof(unsigned int));
    return a;
}

void modifyValue(unsigned int *a, index i, bool val)
{
    bool _val = getValue(a, i);
    if (val == _val)
    {
        return;
    }
    else if (val)
    {
        a[i.y] += 1 << i.x;
    }
    else
    {
        a[i.y] -= 1 << i.x;
    }
}

bool getValue(unsigned int *a, index i)
{
    return a[i.y] >> i.x & 1;
}