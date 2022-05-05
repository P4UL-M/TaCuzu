#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "generation.h"
#include "grid.h"
#include "cache.h"
#include <stdbool.h>
#include <math.h>

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

void freeSizedList(SizedList *l)
{
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

SizedList *extend(SizedList *l1, SizedList *l2)
{
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
    if (restemp != NULL)
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
    add_entry(hashCode(temp), ret);
    return ret;
}

ListSizedList *sortBadSet(ListSizedList *list)
{
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
        if (test && checkDouble(tr, l->size))
        {
            res = appendList(res, l);
        }
    }
    return res;
}

SizedList *sortGrid(SizedList *block, int index, SizedList *remain)
{
    if (block == NULL)
    {
        SizedList *res = (SizedList *)malloc(sizeof(SizedList));
        res->size = 0;
        res->data = NULL;
        block = res;
    }
    if (block->size == 0 || block->size == 1)
    {
        block = append(block, remain->data[index]);
        remain = removeFromIndex(remain, index);
        return sortGrid(block, index, remain);
    }
    if (remain->size > 0)
    {
        int nb = remain->size + block->size - 2;
        bool test = true;
        for (int digit = 0; digit < nb; digit++)
        {
            if (getDigit(remain->data[index], digit) == getDigit(block->data[block->size - 1], digit) && getDigit(remain->data[index], digit) == getDigit(block->data[block->size - 2], digit))
            {
                test = false;
                break;
            }
        }
        if (test)
        {
            block = append(block, remain->data[index]);
            remain = removeFromIndex(remain, index);
            return sortGrid(block, 0, remain);
        }
        else
        {
            if (index == remain->size - 1)
            {
                remain = append(remain, block->data[block->size - 1]);
                block = removeFromIndex(block, block->size - 1);
                return sortGrid(block, 0, remain);
            }
            return sortGrid(block, index + 1, remain);
        }
    }
    return block;
}

void swap(SizedList *l, int i, int j)
{
    unsigned int tmp = l->data[i];
    l->data[i] = l->data[j];
    l->data[j] = tmp;
}

// permutation function
ListSizedList *listGridFromSet(SizedList *arr, int start, int end, ListSizedList *l)
{
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

unsigned int *generate_grid(unsigned int size)
{
    SizedList *lines = list_lines(size);

    int k = size;
    int N = lines->size;
    int P = (pow(2, k) - 1) * k / 2;
    ListSizedList *knapRes = knapsack(0, P, k, lines, N);
    if (lines)
        freeSizedList(lines);

    ListSizedList *sortedSets = sortBadSet(knapRes);
    int index = rand() % sortedSets->size;
    SizedList *res = sortedSets->data[index];
    ListSizedList *grids = listGridFromSet(res, 0, res->size - 1, NULL);
    while (grids->size == 0)
    {
        index = rand() % sortedSets->size;
        res = sortedSets->data[index];
        freeList(grids);
        grids = listGridFromSet(res, 0, res->size - 1, NULL);
    }
    SizedList *grid = copy(grids->data[rand() % grids->size]);
    freeList(sortedSets);
    freeList(grids);
    return grid->data;
}
