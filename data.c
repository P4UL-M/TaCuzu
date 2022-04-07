#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>

int *createArray(int n)
{
    int *a = (int *)malloc(n * sizeof(int));
    return a;
}

void modifyValue(int *a, index i, bool val)
{
    bool _val = getValue(a, i);
    if (val == _val)
    {
        return;
    }
    else if (val)
    {
        a[i.y] += 2 ^ i.x;
    }
    else
    {
        a[i.y] -= 2 ^ i.x;
    }
}

bool getValue(int *a, index i)
{
    return (a[i.y] % i.x) % 2 == 0;
}