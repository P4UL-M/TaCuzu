#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>
#include <time.h>

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

unsigned int *createMask(int size, int difficulty)
{
    unsigned int *m = createArray(size);
    index i;
    int temp, visible=size/difficulty;     //modify calculation
    srand(time(NULL));
    for (i.y=0;i.y<size;i.y++){
        for (i.x = 0 ; i.x < size ; i.x++){
            modifyValue(m, i, 0);
        }
    }
    for (temp = 0 ; temp < visible ; temp++)
    {
        do        
        {
            i.x = rand() % size;
            i.y = rand() % size;
        } while (getValue(m, i) != 0);
        modifyValue(m, i, 1);
    }
    return m;
}