#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>

int main()
{
    int n = 10;
    int *a = createArray(n);
    index i;
    i.x = 4;
    i.y = 0;
    modifyValue(a, i, true);
    printf("%d\n", getValue(a, i));

    return 0;
}
