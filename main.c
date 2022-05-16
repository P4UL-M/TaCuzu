/*TaCuzu
Paul Mairesse and Axel Loones
This file launches the program*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include "generation.h"
#include "cache.h"
#include "user.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>

int main()
{
    /**/
    // user_main();
    int size = 4;
    SizedList *l = list_lines(size);
    printf("%d\n", l->size);
    SizedList *l2 = extractWithPattern(l, 10, 2, 4);
    printf("%d\n", l2->size);

    unsigned int *grid = generate_grid_recc(createArray(size), l, size, 1);
    if (grid != NULL)
    {
        for (int i = 0; i < 16; i++)
        {
            printf("%d\n", grid[i]);
        }
        printf("%d\n", checkArray(grid, size));
    }
    else
    {
        printf("error");
    }
    return 0;
}
