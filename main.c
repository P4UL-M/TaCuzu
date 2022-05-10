#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include "generation.h"
#include "cache.h"
#include <stdbool.h>
#include <math.h>

int main()
{
    int n = 8;
    unsigned int *a = createArray(n);
    unsigned int *m = createMask(n, 1);
    INDEX i;
    i.x = 4;
    i.y = 0;
    //modifyValue(a, i, true);
    // printf("%d\n", getValue(a, i));
    //displayArray(a, n);
    //printf("\nTranspose:\n");
    //displayArray(transpose(a, n), n);
    //printf("\nIt's %d\n", checkArray(a, n));

    a = generate_grid(n);
    //printf("%d\n", checkArray(a, n));
    //displayArray(a, n);
    //displayArray(m, n);

    displayUser(a, m, n);

    i = Obtainable(a, m, n);
    printf("%d, %d\n", i.x, i.y);
    modifyValue(m, i, true);
    displayUser(a, m, n);

    //for (int i = 0; i < 100; i++)
    //{
    //    a = generate_grid(n);
    //    if (checkArray(a, n))
    //    {
    //        displayArray(a, n);
            //break;
    //    }
    //    else
    //    {
    //        printf("%d\n", i);
    //    }
    //    free(a);
    //}

    return 0;
}
