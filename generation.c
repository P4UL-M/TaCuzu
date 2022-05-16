/*TaCuzu
Paul Mairesse and Axel Loones
This file contains all operation for the generation*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include "grid.h"
#include "cache.h"
#include <stdbool.h>
#include <math.h>
#include <time.h>

bool getDigit(unsigned int i, int digit)
{
    // get the digit of i at the digit position
    return i >> digit & 1;
}

int countSetBits(unsigned int i)
{
    // count the number of bits in i
    int count = 0;
    while (i != 0)
    {
        i &= (i - 1);
        count++;
    }
    return count;
}

void freeSizedList(SizedList *l)
{
    // free a matrix
    if (l == NULL)
    {
        return;
    }
    if (l->data != NULL)
    {
        free(l->data);
    }
    free(l);
}

void freeList(ListSizedList *l)
{
    // free a list of matrix
    if (l == NULL)
    {
        return;
    }
    if (l->data != NULL)
    {
        free(l->data);
    }
    free(l);
}

SizedList *list_lines(unsigned int size)
{
    // generate a list of lines with the size given
    int res[(int)pow(2, size)];
    int cpt = 0;

    for (int i = 0; i < pow(2, size); i++) // get all lines possible
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

SizedList *extend(SizedList *l1, SizedList *l2)
{
    // extend a matrix of lines with another matrix given
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l1->size + l2->size;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l1->size; i++)
    {
        res->data[i] = l1->data[i];
    }
    for (int i = 0; i < l2->size; i++)
    {
        res->data[i + l1->size] = l2->data[i];
    }
    return res;
}

SizedList *copy(SizedList *l)
{
    // copy a matrix
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l->size;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    return res;
}

SizedList *append(SizedList *l, unsigned int e)
{
    // append an element to a matrix
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l->size + 1;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    res->data[l->size] = e;
    freeSizedList(l);
    return res;
}

SizedList *removeFromIndex(SizedList *l, unsigned int index)
{
    // remove an element from a matrix
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->size = l->size - 1;
    res->data = (unsigned int *)malloc(sizeof(unsigned int) * res->size);
    for (int i = 0; i < index; i++)
    {
        res->data[i] = l->data[i];
    }
    for (int i = index; i < l->size - 1; i++)
    {
        res->data[i] = l->data[i + 1];
    }
    freeSizedList(l);
    return res;
}

ListSizedList *appendList(ListSizedList *l, SizedList *e)
{
    // append a matrix to a list of matrix
    ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
    res->size = l->size + 1;
    res->data = (SizedList **)malloc(sizeof(SizedList *) * res->size);
    for (int i = 0; i < l->size; i++)
    {
        res->data[i] = l->data[i];
    }
    res->data[l->size] = e;
    freeList(l);
    return res;
}

ListSizedList *extendList(ListSizedList *l1, ListSizedList *l2)
{
    // extend a list of matrix with another list of matrix given
    ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
    res->size = l1->size + l2->size;
    res->data = (SizedList **)malloc(sizeof(SizedList *) * res->size);
    for (int i = 0; i < l1->size; i++)
    {
        res->data[i] = l1->data[i];
    }
    for (int i = 0; i < l2->size; i++)
    {
        res->data[i + l1->size] = l2->data[i];
    }
    return res;
}

ListSizedList *knapsack(int i, int target, int k, SizedList *A, int N)
{
    // recursive function to give the list of set with a sum of k
    if (i > N - k)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 0;
        res->data = NULL;
        return res;
    }
    if (target == 0 && k == 0)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 1;
        res->data = (SizedList **)malloc(sizeof(SizedList *));
        res->data[0] = (SizedList *)malloc(sizeof(SizedList));
        res->data[0]->size = 0;
        res->data[0]->data = NULL;
        return res;
    }
    if (k <= 0)
    {
        ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
        res->size = 0;
        res->data = NULL;
        return res;
    }
    unsigned int tmpdata[] = {i, target, k};
    SizedList *temp = (SizedList *)malloc(sizeof(SizedList));
    temp->size = 3;
    temp->data = (unsigned int *)malloc(sizeof(unsigned int) * temp->size);
    for (int i = 0; i < temp->size; i++)
    {
        temp->data[i] = tmpdata[i];
    }
    ListSizedList *restemp = find_entry(hashCode(temp));
    if (restemp != NULL) // if the entry has already been computed and store into the hash table
    {
        return restemp;
    }
    ListSizedList *ret = (ListSizedList *)malloc(sizeof(ListSizedList));
    ret->size = 0;
    ret->data = NULL;
    ListSizedList *res = knapsack(i + 1, target - A->data[i], k - 1, A, N);
    for (int j = 0; j < res->size; j++)
    {
        SizedList *new = copy(res->data[j]);
        new = append(new, A->data[i]);
        ret = appendList(ret, new);
    }
    ret = extendList(ret, knapsack(i + 1, target, k, A, N));
    add_entry(hashCode(temp), ret); // add the entry to the hash table
    return ret;
}

ListSizedList *sortBadSet(ListSizedList *list)
{
    // remove every set from the list that cannot be grid
    ListSizedList *res = (ListSizedList *)malloc(sizeof(ListSizedList));
    res->size = 0;
    res->data = NULL;
    for (int j = 0; j < list->size; j++)
    {
        SizedList *l = list->data[j];
        unsigned int *tr = transpose(l->data, l->size);
        bool test = true;
        for (int i = 0; i < l->size; i++)
        {
            if (countBits(tr[i]) != l->size / 2)
            {
                test = false;
                break;
            }
        }
        if (test)
        {
            res = appendList(res, l);
        }
    }
    return res;
}

void swap(SizedList *l, int i, int j)
{
    // swap two elements of a list
    unsigned int tmp = l->data[i];
    l->data[i] = l->data[j];
    l->data[j] = tmp;
}

ListSizedList *listGridFromSet(SizedList *arr, int start, int end, ListSizedList *l)
{
    // recursive function to give the list of grid from a set
    if (l == NULL)
    {
        l = (ListSizedList *)malloc(sizeof(ListSizedList));
        l->size = 0;
        l->data = NULL;
    }
    if (start == end)
    {
        if (checkArray(arr->data, arr->size))
        {
            l = appendList(l, copy(arr));
        }
        return l;
    }
    int i;
    for (i = start; i <= end; i++)
    {
        // swapping numbers
        swap(arr, i, start);
        // fixing one first digit
        // and calling permutation on
        // the rest of the digits
        l = listGridFromSet(arr, start + 1, end, l);
        swap(arr, i, start);
    }
    return l;
}

unsigned int *generate_grid2(unsigned int size)
{
    // generate a grid of size size

    // get the list of possible lines
    SizedList *lines = list_lines(size);
    srand(time(NULL));

    int k = size;
    int N = lines->size;
    int P = (pow(2, k) - 1) * k / 2;
    // get the list of possible sets
    ListSizedList *knapRes = knapsack(0, P, k, lines, N);
    if (lines)
        freeSizedList(lines);

    // remove every set that cannot be grid
    ListSizedList *sortedSets = sortBadSet(knapRes);
    int index = rand() % sortedSets->size;
    SizedList *res = sortedSets->data[index];
    // get the list of possible grids of a set
    ListSizedList *grids = listGridFromSet(res, 0, res->size - 1, NULL);
    while (grids->size == 0) // secure that there is at least one grid
    {
        index = rand() % sortedSets->size;
        res = sortedSets->data[index];
        freeList(grids);
        grids = listGridFromSet(res, 0, res->size - 1, NULL);
    }
    // get a random grid
    SizedList *grid = copy(grids->data[rand() % grids->size]);
    freeList(sortedSets);
    freeList(grids);
    // return the grid
    return grid->data;
}

// WIP
unsigned int xnor(unsigned int a, unsigned int b, int size);
SizedList *extractWithPattern(SizedList *lines, unsigned int pattern, unsigned int sizePattern, unsigned int size);
unsigned int *generate_grid_recc(unsigned int *grid, SizedList *lines, unsigned int size, unsigned int index);
bool isInList(unsigned int *list, unsigned int value, int size);
unsigned int *generate_grid(unsigned int size)
{
    // get all lines
    SizedList *lines = list_lines(size);
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));

    srand(time(NULL));
    for (int i = 0; i < 2; i++)
    {
        int tmp = rand() % lines->size;
        printf("adding : %d\n", lines->data[tmp]);
        res = append(res, lines->data[tmp]);
        lines = removeFromIndex(lines, tmp);
    }

    // return generate_grid_recc(res, lines, size);
}

unsigned int *generate_grid_recc(unsigned int *grid, SizedList *lines, unsigned int size, unsigned int index)
{
    if (index == size * 2 + 1)
    {
        return grid;
    }
    grid = transpose(grid, size);
    int local_index = (int)index / 2;
    if (index == 1)
    {
        srand(time(NULL));
        grid[0] = lines->data[rand() % lines->size];
        return generate_grid_recc(grid, lines, size, index + 1);
    }
    unsigned int tempIndex = local_index - 1 + index % 2;
    unsigned int l1;
    unsigned int l2;
    if (index > 4)
    {
        l1 = grid[tempIndex - 1];
        l2 = grid[tempIndex - 2];
    }
    SizedList *extractlines = extractWithPattern(lines, grid[tempIndex], local_index, size);
    int offset = rand() % extractlines->size;
    for (int i = offset; i < extractlines->size + offset; i++)
    {
        if (index > 4)
        {
            if ((xnor(l1, l2, size) & xnor(extractlines->data[i % offset], l1, size)) == 0 && !isInList(grid, extractlines->data[i % offset], tempIndex))
            {
                grid[tempIndex] = extractlines->data[i % offset];
                // find a way to remove doubles
                unsigned int *res = generate_grid_recc(grid, lines, size, index + 1);
                if (res != NULL)
                {
                    return res;
                }
            }
        }
        else
        {
            if (!isInList(grid, extractlines->data[i % offset], tempIndex))
            {
                grid[tempIndex] = extractlines->data[i % offset];
                // find a way to remove doubles
                unsigned int *res = generate_grid_recc(grid, lines, size, index + 1);
                if (res != NULL)
                {
                    return res;
                }
            }
        }
    }
    printf("returning NULL %d\n", index);
    return NULL;
}

unsigned int xnor(unsigned int a, unsigned int b, int size)
{
    unsigned int res = 0;
    for (int i = 0; i < size; i++)
    {
        res += ((~((a >> i) & 1) ^ ((b >> i) & 1)) & 1) << i;
    }
    return res;
}

SizedList *extractWithPattern(SizedList *lines, unsigned int pattern, unsigned int sizePattern, unsigned int size)
{
    SizedList *res = (SizedList *)malloc(sizeof(SizedList));
    res->data = NULL;
    res->size = 0;
    for (int line = 0; line < lines->size; line++)
    {
        bool test = true;
        for (int digit = 0; digit < sizePattern; digit++)
        {
            if (((lines->data[line] >> digit) & 1) != ((pattern >> digit) & 1))
            {
                test = false;
                break;
            }
        }
        if (test)
        {
            res = append(res, lines->data[line]);
        }
    }
    return res;
}

bool isInList(unsigned int *list, unsigned int value, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == value)
        {
            return true;
        }
    }
    return false;
}