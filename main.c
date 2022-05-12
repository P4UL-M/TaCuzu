#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include "generation.h"
#include "cache.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>

int main()
{
    int n = 8;
    clock_t t;
    t = clock();
    unsigned int *a = generate_grid(n);
    t = clock() - t;
    printf("Generation time: %f\n", ((float)t) / CLOCKS_PER_SEC);
    unsigned int *m = createMask(n, 1);
    INDEX *i;
    i = (INDEX *)malloc(sizeof(INDEX));
    i->x = 4;
    i->y = 0;

    displayUser(a, m, n);
    int cpt;
    for (cpt = 0; cpt < 24; cpt++)
    {
        free(i);
        i = Obtainable(a, m, n);
        if (i != NULL)
        {
            printf("not in transpose %d, %d\n", i->x, i->y);
            printf("%d, %d\n", i->x, i->y);
            modifyValue(m, *i, true);
            displayUser(a, m, n);
        }
        else
        {
            unsigned int *t = transpose(a, n);
            unsigned int *t_mask = transpose(m, n);
            free(i);
            i = Obtainable(t, t_mask, n);
            free(t);
            free(t_mask);
            if (i != NULL)
            {
                int temp = i->x;
                i->x = i->y;
                i->y = temp;

                printf("in transpose %d, %d\n", i->x, i->y);
                modifyValue(m, *i, true);
                displayUser(a, m, n);
            }
            else
            {
                INDEX temp;
                temp.x = 0;
                temp.y = 0;
                i = Hypothesis(a, m, n, temp);
                if (i != NULL)
                {
                    printf("HYPOTHESISSSSS %d, %d\n", i->x, i->y);
                    modifyValue(m, *i, true);
                    displayUser(a, m, n);
                }
                else
                {

                    printf("No more possible after %d resolutions\n", cpt);
                }
            }
        }
    }
    printf("%d\n", cpt);

    return 0;
}
