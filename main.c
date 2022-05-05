#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include "generation.h"
#include <stdbool.h>

int main()
{
    int n = 8;
    // unsigned int *a = createArray(n);
    unsigned int *a = createMask(n, 3);
    index i;
    i.x = 4;
    i.y = 0;
    modifyValue(a, i, true);
    // printf("%d\n", getValue(a, i));
    displayArray(a, n);
    printf("\nTranspose:\n");
    displayArray(transpose(a, n), n);
    printf("\nIt's %d\n", checkArray(a, n));
    SizedList *lines = list_lines(n);
    for (int i = 0; i < lines->size; i++)
    {
        printf("%d, ", lines->data[i]);
    }
    printf("\nSize: %d\n", lines->size);
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
