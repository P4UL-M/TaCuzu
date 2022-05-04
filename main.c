#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include <stdbool.h>

int main()
{
    int n = 16;
    // unsigned int *a = createArray(n);
    unsigned int *a = createMask(n, 3);
    index i;
    i.x = 4;
    i.y = 0;
    modifyValue(a, i, true);
    // printf("%d\n", getValue(a, i));
    displayArray(a, n);
    // printf("\033[0;31m");
    // for (i.y = 0; i.y < n; i.y++)
    // {
    //     for (i.x = 0; i.x < n; i.x++)
    //     {
    //         printf("%d ", getValue(a, i));
    //     }
    //     printf("\n");
    // }
    // printf("\033[0m");
    return 0;
}
