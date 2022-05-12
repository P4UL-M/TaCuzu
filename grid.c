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
    int difficulties[] = {10, 5, 3};                                                                         // levels of difficulty
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
            printf("%d", getValue(a, i)); // print the value of the cell
        }
        printf(ANSI_COLOR_RESET); // reset the color
        printf("\n");
    }
}

void displayUser(unsigned int *sol, unsigned int *mask, int n)
{
    INDEX i;
    int temp;
    for (i.y = 0; i.y < n; i.y++)
    {
        for (i.x = 0; i.x < n; i.x++)
        {
            if (getValue(mask, i))
            {
                temp = getValue(sol, i);
                if (temp)
                {
                    printf(ANSI_COLOR_RED);
                }
                else
                {
                    printf(ANSI_COLOR_BLUE);
                }
                printf("%d", getValue(sol, i));
            }
            else
            {
                printf(" ");
            }
        }
        printf(ANSI_COLOR_RESET);
        printf("\n");
    }
}

bool checkDouble(unsigned int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    { // read comment by @nbro
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
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
        for (int digit = 0; digit < nb; digit++) // check no more than 3 successive identical values
        {
            if (getdigit(a[i], digit) == getdigit(a[i], digit + 1) && getdigit(a[i], digit) == getdigit(a[i], digit + 2))
            {
                return false;
            }
        }
        if (countBits(a[i]) != n / 2) // check if there are as many 0s as 1s
        {
            return false;
        }
    }
    if (!checkDouble(a, n))
    {
        return false;
    }

    unsigned int *t = transpose(a, n); // check for the columns
    for (int i = 0; i < n; i++)
    {
        int nb = n - 2;
        for (int digit = 0; digit < nb; digit++)
        {
            if (getdigit(t[i], digit) == getdigit(t[i], digit + 1) && getdigit(t[i], digit) == getdigit(t[i], digit + 2))
            {
                return false;
            }
        }
        if (countBits(t[i]) != n / 2) // check if there are as many 0s as 1s
        {
            return false;
        }
    }
    if (!checkDouble(t, n))
    {
        return false;
    }
    return true;
}

bool checkValid(unsigned int *a, unsigned int *mask, int n)
{
    for (int i = 0; i < n; i++)
    {
        int nb = n - 2;
        for (int digit = 0; digit < nb; digit++) // check no more than 3 successive identical values
        {
            if (getdigit(mask[i], digit) && getdigit(mask[i], digit + 1) && getdigit(mask[i], digit + 2))
            {
                if (getdigit(a[i], digit) == getdigit(a[i], digit + 1) && getdigit(a[i], digit) == getdigit(a[i], digit + 2))
                {
                    return false;
                }
            }
        }
        if (countBits(a[i]) != n / 2) // check if there are as many 0s as 1s
        {
            return false;
        }
    }
    if (!checkDouble(a, n))
    {
        return false;
    }

    unsigned int *t = transpose(a, n); // check for the columns
    for (int i = 0; i < n; i++)
    {
        int nb = n - 2;
        for (int digit = 0; digit < nb; digit++)
        {
            if (getdigit(mask[i], digit) && getdigit(mask[i], digit + 1) && getdigit(mask[i], digit + 2))
            {
                if (getdigit(a[i], digit) == getdigit(a[i], digit + 1) && getdigit(a[i], digit) == getdigit(a[i], digit + 2))
                {
                    return false;
                }
            }
        } // no need to check again number of 1s
    }     // same for identical columns

    return true;
}

INDEX *Obtainable(unsigned int *sol, unsigned int *mask, int n)
{
    INDEX *index = (INDEX *)malloc(sizeof(INDEX));
    for (int i = 0; i < n; i++)
    {
        for (int digit = 1; digit < n - 1; digit++)
        {
            if (getdigit(sol[i], digit - 1) == getdigit(sol[i], digit) && 1 == getdigit(mask[i], digit - 1) && getdigit(mask[i], digit) == 1)
            {
                if (getdigit(mask[i], digit + 1) != 1)
                {
                    index->y = i;
                    index->x = digit + 1;
                    printf("After two %ds, there can only be a %d\n", getdigit(sol[i], digit), !getdigit(sol[i], digit));
                    return index; // Because grid inverted
                }
            }
            if (getdigit(sol[i], digit - 1) == getdigit(sol[i], digit + 1) && 1 == getdigit(mask[i], digit - 1) && getdigit(mask[i], digit + 1) == 1)
            {
                if (getdigit(mask[i], digit) != 1)
                {
                    index->x = digit;
                    index->y = i;
                    printf("Between two %ds, there can only be a %d\n", getdigit(sol[i], digit - 1), !getdigit(sol[i], digit - 1));
                    return index;
                }
            }
            if (getdigit(sol[i], digit) == getdigit(sol[i], digit + 1) && 1 == getdigit(mask[i], digit) && getdigit(mask[i], digit + 1) == 1)
            {
                if (getdigit(mask[i], digit - 1) != 1)
                {
                    index->y = i;
                    index->x = digit - 1;
                    printf("Before two %ds, there can only be a %d\n", getdigit(sol[i], digit), !getdigit(sol[i], digit));
                    return index; // Because grid inverted
                }
            }
        }
        if (countBits(sol[i] & mask[i]) == n / 2 && countBits(mask[i]) < n)
        {
            index->y = i;
            index->x = 0;
            while (getdigit(mask[i], index->x) == 1)
            {
                index->x++;
            }
            printf("There can only be %d 1 on line/columns %d\n", n / 2, index->y);
            return index;
        }
        if (countBits(~sol[i] & mask[i]) == n / 2 && countBits(mask[i]) < n)
        {
            index->y = i;
            index->x = 0;
            while (getdigit(mask[i], index->x) == 1)
            {
                index->x++;
            }
            printf("There can only be %d 0 on line/columns %d\n", n / 2, index->y);
            return index;
        }
        if (countBits(mask[i]) == n - 1) // check number of values
        {
            printf("%d on line %d\n", countBits(mask[i]), i);
            index->y = i;
            index->x = 0;
            while (getdigit(mask[i], index->x) == 1)
            {
                index->x++;
            }
            printf("There can only be one value for %d,%d since line is missing only 1 value\n", index->x, index->y);
            return index;
        }
        if (countBits(mask[i]) == n - 2) // check doublons
        {
            for (int lines = 0; lines < n; lines++)
            {
                if (countBits(mask[lines]) == n && i != lines)
                {
                    bool isdouble = true;
                    for (int digit = 1; digit < n; digit++)
                    {
                        if (getdigit(sol[i], digit) != getdigit(sol[lines], digit) && 1 == getdigit(mask[i], digit) && 1 == getdigit(mask[lines], digit))
                        {
                            isdouble = false;
                            break;
                        }
                    }
                    // check if lines who could be a double if we add wrong value
                    if (isdouble)
                    {
                        index->y = i;
                        index->x = 0;
                        while (getdigit(mask[i], index->x) == 1)
                        {
                            index->x++;
                        }
                        printf("There can only be one value for %d,%d since line %d would be a double of actual line\n", index->x, index->y, lines);
                        return index;
                    }
                }
            }
        }
    }
    return NULL;
}