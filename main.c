#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>

int main()
{
    int n = 10;
    //unsigned int *a = createArray(n);
    unsigned int *a = createMask(n, 5);
    index i;
    i.x = 4;
    i.y = 0;
    modifyValue(a, i, true);
    //printf("%d\n", getValue(a, i));
    for (i.y=0;i.y<n;i.y++){
        for (i.x=0;i.x<n;i.x++){
            printf("%d\t", getValue(a, i));
        }
        printf("\n");
    }
    return 0;
}
