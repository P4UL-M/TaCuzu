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

bool getdigit(unsigned int i, int digit)
{
    return i >> digit & 1;
}

int countBits(unsigned int i)
{
    int count = 0;
    while (i != 0)
    {
        i &= (i - 1);
        count++;
    }
    return count;
}

unsigned int *createMask(int size, int difficulty)
{
    unsigned int *m = createArray(size);
    // difficulty go from 1 to 3
    INDEX i;
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
    INDEX i;
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

bool checkDouble(unsigned int *a, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        int temp = a[i];
        for (int j = i + 1; j < n-1; j++)
        {
            if (a[j] == temp)
            {
                return false;
            }
        }
    }
    return true;
}

bool checkArray(unsigned int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int nb = n - 2;
        for (int digit = 0; digit < nb; digit++)    // check no more than 3 successive identical values
        {
            if (getdigit(a[i], digit) == getdigit(a[i], digit + 1) && getdigit(a[i], digit) == getdigit(a[i], digit + 2))
            {
                return false;
            }
        }
        if (countBits(a[i]) != n / 2)            // check if there are as many 0s as 1s
        {
            return false;
        }
    }
    if (!checkDouble(a, n)){
        return false;
    }

    unsigned int *t = transpose(a, n);              // check for the columns
    for (int i = 0; i < n; i++)
    {
        int nb = n - 2;
        for (int digit = 0; digit < nb; digit++)
        {
            if (getdigit(t[i], digit) == getdigit(t[i], digit + 1) && getdigit(t[i], digit) == getdigit(t[i], digit + 2))
            {
                return false;
            }
        }                                           // no need to check again number of 1s
    }                                               // same for identical columns
    return true;
}
