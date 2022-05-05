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
    // unsigned int *a = createArray(n);
    unsigned int *a = createMask(n, 3);
    INDEX i;
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
    int k = n;
    int N = lines->size;
    int P = pow(2, k + 1) - 2;
    printf("%d\n", P);
    ListSizedList *res = knapsack(0, P, k, lines, N);
    printf("%d\n", res->data[0]->size);
    for (int j = 0; j < res->size; j++)
    {
        for (int i = 0; i < res->data[j]->size; i++)
        {
            printf("%d, ", res->data[j]->data[i]);
        }
        printf("\n");
    }
    return 0;
}
