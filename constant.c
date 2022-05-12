#include "constant.h"

//All constants you want to modify in your code

char *Default_mask4x4[]={
    "1000",
    "0110",
    "0100",
    "0001"
};

char *Default_sol4x4[]={
    "0011",
    "0110",
    "1100",
    "1001"
};

char *Default_mask8x8[]={
    "01001111",
    "01011111",
    "10111010",
    "00100110",
    "10100111",
    "01101011",
    "01001111",
    "11110101"
};

char *Default_sol8x8[]={
    "11110000",
    "01111000",
    "00111100",
    "00011110",
    "00001111",
    "10000111",
    "11000011",
    "11100001"
};

unsigned int *convert(char **grid, int n)
{
    unsigned int *res = (unsigned int*)malloc(n * sizeof(unsigned int));
    for (unsigned int line = 0; line < n; line++)
    {
        int a=0;
        char *dline = grid[line];
        for (int i = 0; i < n; i++)
        {
            if (dline[i] - '0'){
                a += pow(2, n - i - 1);
            }
        }
        res[line] = a;
    }
    return res;
}

unsigned int *getDefaultGrid(int size)
{
    if (size == 4)
    {
        return convert(Default_sol4x4, 4);
    }
    else
    {
        return convert(Default_sol8x8, 8);
    }
}

unsigned int *getDefaultMask(int size)
{
    if (size == 4)
    {
        return convert(Default_mask4x4, 4);
    }
    else
    {
        return convert(Default_mask8x8, 8);
    }
}
