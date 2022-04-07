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
    printf("val : %d\n", a[i.y]);
    if (val == _val)
    {
        return;
    }
    else if (val)
    {
        printf("adding %d\n", 1 << i.x);
        a[i.y] += 1 << i.x;
    }
    else
    {
        a[i.y] -= 1 << i.x;
    }
    printf("val : %d\n", a[i.y]);
}

bool getValue(int *a, index i)
{
    return a[i.y] >> i.x & 1;
}