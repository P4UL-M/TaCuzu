#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "grid.h"
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

unsigned int *createMask(int size, int difficulty)
{
    unsigned int *m = createArray(size);
    // difficulty go from 1 to 3
    index i;
    int difficulties[] = {8, 5, 3};                                                                          // levels of difficulty
    int temp, nb_visible;                                                                                    // get the number of visible cells
    nb_visible = difficulties[difficulty - 1] * (int)pow((double)2, (size / 4 != 1) ? (double)size / 4 : 0); // factor to size of the grid
    srand(time(NULL));                                                                                       // seed the random generator
    for (temp = 0; temp < nb_visible; temp++)
    {
        do
        {
            i.x = rand() % size;
            i.y = rand() % size;
        } while (getValue(m, i) != 0); // check if the cell is already visible
        modifyValue(m, i, 1);          // set the cell to visible
    }
    return m; // return the mask
}

void displayArray(unsigned int *a, int n)
{
    index i;
    int temp;
    for (i.y = 0; i.y < n; i.y++)
    {
        for (i.x = 0; i.x < n; i.x++)
        {
            temp = getValue(a, i);
            if (temp) // change color of the cell depending on the value
            {
                printf(ANSI_COLOR_RED);
            }
            else
            {
                printf(ANSI_COLOR_BLUE);
            }
            printf("%d ", getValue(a, i)); // print the value of the cell
        }
        printf(ANSI_COLOR_RESET); // reset the color
        printf("\n");
    }
}