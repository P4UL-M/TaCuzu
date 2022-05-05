#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include "generation.h"
#include "cache.h"
#include <stdbool.h>

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
    SizedList *lines = list_lines(n);
    for (int i = 0; i < lines->size; i++)
    {
        printf("%d, ", lines->data[i]);
    }
    printf("\nSize: %d\n", lines->size);

    SizedList test = (SizedList){.size = 3, .data = lines->data};
    add_entry(&test);
    long long int hash = hashCode(&test);
    SizedList *res = find_entry(hash);
    printf("%d, %d, %d\n", test.data[0], test.data[1], test.data[2]);
    printf("%d, %d, %d\n", res->data[0], res->data[1], res->data[2]);
    return 0;
}
