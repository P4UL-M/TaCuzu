/*TaCuzu
Paul Mairesse and Axel Loones
Basic functions to modify array*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
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

unsigned int *createArray(int n)
// To create a 1D array of size n initialized to 0
{
    unsigned int *a = (unsigned int *)malloc(n * sizeof(unsigned int));
    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
    }
    return a;
}

void modifyValue(unsigned int *a, INDEX i, bool val)
// Modify the value of index i
{
    bool _val = getValue(a, i);
    if (val == _val)
    {
        return;
    }
    else if (val)
    {
        a[i.y] += 1 << i.x;
    }
    else
    {
        a[i.y] -= 1 << i.x;
    }
}

bool getValue(unsigned int *a, INDEX i)
// Return the value at index i
{
    return a[i.y] >> i.x & 1;
}

unsigned int *transpose(unsigned int *a, int n)
// Make the transpose of the grid to make an easy check for rows/columns
{
    unsigned int *t = createArray(n);
    INDEX i, i_;
    for (i.y = 0; i.y < n; i.y++)
    {
        for (i.x = 0; i.x < n; i.x++)
        {
            i_.x = i.y;
            i_.y = i.x;
            modifyValue(t, i, getValue(a, i_)); // To get easily the columns
        }
    }
    return t;
}

unsigned int sum(unsigned int *a, int n)
// Make the sum of all values
{
    unsigned int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

bool is_in(unsigned int *a, int n, unsigned int val)
// Check if a line is already in the grid
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == val)
        {
            return true;
        }
    }
    return false;
}