#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include <stdbool.h>
#include <math.h>

unsigned int *generate_grid(unsigned int size)
{
    unsigned int *a = createArray(size);
    return a;
}

bool getDigit(unsigned int i, int digit)
{
    return i >> digit & 1;
}

int countSetBits(unsigned int i)
{
    int count = 0;
    while (i != 0)
    {
        i &= (i - 1);
        count++;
    }
    return count;
}

SizedList *list_lines(unsigned int size)
{
    int res[(int)pow(2, size)];
    int cpt = 0;

    for (int i = 0; i < pow(2, size); i++) // get lines that work
    {
        int nb = size - 2;
        bool isValid = true;
        for (int digit = 0; digit < nb; digit++) // check successive digits
        {
            int a = getDigit(i, digit);
            int b = getDigit(i, digit + 1);
            int c = getDigit(i, digit + 2);
            if (a == b && b == c)
            {
                isValid = false;
                break;
            }
        }
        if (isValid && countSetBits(i) == size / 2) // check number of set bits
        {
            res[cpt] = i;
            cpt++;
        }
    }
    SizedList *res_ = (SizedList *)malloc(sizeof(SizedList));
    res_->size = cpt;
    res_->data = (unsigned int *)malloc(sizeof(unsigned int) * cpt);
    for (int i = 0; i < cpt; i++)
    {
        res_->data[i] = res[i];
    }
    return res_;
}