/*TaCuzu
Paul Mairesse and Axel Loones
All constants you want to modify in your code and function to access it*/
#include "constant.h"

//Default grids, change them if you want!
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
    "01011001",
    "10011010",
    "10100110",
    "01001101",
    "00110011",
    "11010100",
    "10101001",
    "01100110"
};


unsigned int *convert(char **grid, int n)
// Transform the 2D list in a 1D list for the rest of the program
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
//To get the default grid
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
//To get the default mask
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
